/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/04 15:34:52 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* get next room and weight from link structure */
void	get_next_weight(t_link *link, t_room *curr, t_room **next, int *weight)
{
	*weight = link->one_two;
	*next = link->room2;
	if (curr == link->room2)
	{
		*weight = link->two_one;
		*next = link->room1;
	}
}

/* get path length */
t_bool	get_path_len(t_info *info, t_room **prev, t_path *path)
{
	t_room	*tmp;

	tmp = info->end_room;
	path->len = 0;
	while (tmp != NULL)
	{
		tmp = prev[tmp->index];
		path->len++;
	}
	path->path = (t_room **)malloc(sizeof(t_room *) * path->len);
	if (path->path == NULL)
		return (FALSE);
	return (TRUE);
}

/* get the path from prev[info->room] array in bfs */

t_path	*reverse_path(t_info *info, t_room **prev)
{
	t_room	*tmp;
	t_path	*path;
	int		index;

	index = 0;
	if (prev[info->end_room->index] == NULL)
		return (NULL);
	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);
	if (get_path_len(info, prev, path) == FALSE)
	{
		free(path);
		return (NULL);
	}
	index = path->len - 1;
	tmp = info->end_room;
	while (tmp)
	{
		path->path[index] = tmp;
		tmp = prev[tmp->index];
		index--;
	}
	path->next = NULL;
	return (path);
}

/*initiarize bfs struct */
t_bool	init_bfs(t_info *info, t_bfs *b)
{
	b->visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (b->visited == NULL)
		return (FALSE);
	ft_memset(b->visited, 0, sizeof(t_bool) * info->total_rooms);
	b->prev = (t_room ***)malloc(sizeof(t_room **) * info->start_room->malloc_link);
	for (int i = 0; i < info->start_room->malloc_link; i++)
	{
		b->prev[i] = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
		if (b->prev[i] == NULL)
			return (FALSE);
		ft_memset(b->prev[i], 0, sizeof(t_room *) * info->total_rooms);
	}
	b->head = create(info->start_room);
	b->tail = b->head;
	b->visited[info->start_room->index] = TRUE;
	return (TRUE);
}

void	bfs_condition(t_info *info, t_bfs *b, t_room *curr)
{
	int		weight;
	t_room	*next;
	int		index;

	index = 0;
	while (index < curr->malloc_link)
	{
		if (curr->link[index] == NULL)
			continue ;
		get_next_weight(curr->link[index], curr, &next, &weight);
		if (b->visited[next->index] == FALSE && weight != 1)
		{
			if (curr == info->start_room)
				next->path_nb = index;
			else
				next->path_nb = curr->path_nb;
			push(&(b->tail), &(b->head), create(next));
			b->prev[next->path_nb][next->index] = curr;
			b->visited[next->index] = TRUE;
		}
		//printf("to:%s weight = %d next->path_nb = %d\n", next->room_name, weight, next->path_nb);
		if (b->prev[next->path_nb][info->end_room->index])
			break ;
		index++;
	}
}

t_bool	is_visited(t_bfs *b, t_room *curr, t_room *next)
{
	t_room	*tmp;

	tmp = curr;
	while (tmp != NULL)
	{
		tmp = b->prev[curr->path_nb][tmp->index];
		if (tmp == next)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	is_first_inverse_edge(t_bfs *b, t_room *room)
{
	t_room	*prev;
	t_room	*curr;
	t_room	*tmp;
	int		weight;

	tmp = room;
	while (tmp != NULL)
	{
		curr = tmp;
		prev = b->prev[curr->path_nb][curr->index];
		for (int i = 0; i < curr->malloc_link; i++)
		{
			if (curr->link[i]->room1 == prev || curr->link[i]->room2 == prev)
			{
				weight = curr->link[i]->one_two;
				if (curr->link[i]->room2 == prev)
					weight = curr->link[i]->two_one;
				if (weight == -1)
					return (TRUE);
			}
		}
		tmp = b->prev[curr->path_nb][tmp->index];
	}
	return (FALSE);
}

/*
 * test if there are inverse edge to go
 *
 * If we can get to a vertex v which is used by a path,
 * but the predecessor was not in a path, then we must now follow the path backward.
 *
 * e.g.
 *
 * g -> e & g -> k: g -> e is an inverse edge, so skip K
 * j -> g : is an inverse edge
 * g -> k & g -> e: used an inverse edge already so we are allowed to "jump off" to any neighbor
 * e -> b : visited, so not going
 */
t_bool	find_next_edge(t_info *info, t_bfs *b, t_room *curr)
{
	int		index;
	int		weight;
	t_room	*next;

	index = 0;
	while (index < curr->malloc_link)
	{
		get_next_weight(curr->link[index], curr, &next, &weight);
		if (weight == -1)
		{
			/* check if the room is already visited in the path */
			if (is_visited(b, curr, next))
				return (FALSE);
			/* If we are already following a path backward, then we are allowed to "jump off" to any neighbor.*/
			if (is_first_inverse_edge(b, curr))
				return (FALSE);
			if (curr == info->start_room)
				next->path_nb = index;
			else
				next->path_nb = curr->path_nb;
			push(&(b->tail), &(b->head), create(next));
			b->prev[next->path_nb][next->index] = curr;
			b->visited[next->index] = TRUE;
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

t_path *bfs(t_info *info)
{
	t_bfs	b;
	t_path	*path;
	t_room	*curr;

	path = NULL;
	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	while (b.head)
	{
		curr = pop(&(b.head));
		//printf("curr = %s\n", curr->room_name);
		if (find_next_edge(info, &b, curr) == FALSE)
		{
		//	printf("PASS\n");
			bfs_condition(info, &b, curr);
		}
		//print_que(b.head, &b);
	}
	path = reverse_path(info, b.prev[info->end_room->path_nb]);
	/*
	for (int i = 0; i < info->start_room->malloc_link; i++)
	{
		if (b.prev[i] == NULL)
			printf("NULL\n");
		for (int j = 0; j < info->total_rooms; j++)
		{
			if (b.prev[i][j] == NULL)
				printf("0 ");
			else
				printf("[%3s] ", b.prev[i][j]->room_name);
		}
		printf("\n");
	}
	*/
	free_que(b.head);
	free_bfs(&b);
	return (path);
}

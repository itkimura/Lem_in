/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/03 22:32:19 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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
	int	index;

	index = 0;
	b->visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (b->visited == NULL)
		return (FALSE);
	ft_memset(b->visited, 0, sizeof(t_bool) * info->total_rooms);
	b->prev = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
	if (b->prev == NULL)
		return (FALSE);
	ft_memset(b->prev, 0, sizeof(t_room *) * info->total_rooms);
	b->distance = (int *)malloc(sizeof(int) * info->total_rooms);
	if (b->distance == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		(b->distance)[index] = INT_MAX;
		index++;
	}
	b->distance[info->start_room->index] = 0;
	b->head = create(info->start_room);
	b->tail = b->head;
	b->visited[info->start_room->index] = TRUE;
	return (TRUE);
}

void	bfs_condition(t_bfs *b, t_room *curr, int index)
{
	int		weight;
	t_room	*to;

	if (curr->link[index] == NULL)
		return ;
	weight = curr->link[index]->one_two;
	to = curr->link[index]->room2;
	if (curr->link[index]->room2 == curr)
	{
		weight = curr->link[index]->two_one;
		to = curr->link[index]->room1;
	}
	//printf("from:%s to:%s weight = %d index = %d curr->malloc_link = %d\n", from->room_name, to->room_name, weight, index, curr->malloc_link);
	if (b->visited[to->index] == FALSE && weight != 1)
	{
		push(&(b->tail), &(b->head), create(to));
		b->prev[to->index] = curr;
		b->visited[to->index] = TRUE;
	}
}

t_bool	is_visited(t_bfs *b, t_room *curr, t_room *next)
{
	t_room	*tmp;

	tmp = curr;
	while (tmp != NULL)
	{
		tmp = b->prev[tmp->index];
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
		prev = b->prev[curr->index];
		for (int i = 0; i < curr->malloc_link; i++)
		{
			if (curr->link[i]->room1 == prev || curr->link[i]->room2 == prev)
			{
				weight  = curr->link[i]->one_two;
				if (curr->link[i]->room2 == prev)
					weight = curr->link[i]->two_one;
				if (weight == -1)
					return (TRUE);
			}
		}
		tmp = b->prev[tmp->index];
	}
	return (FALSE);
}

/* test if there are inverse edge*/
t_room	*find_next_edge(t_bfs *b, t_room *curr)
{
	int		index;
	int		weight;
	t_link	*link;
	t_room	*to;

	index = 0;
	/*
	 * If we can get to a vertex v which is used by a path,
	 * but the predecessor was not in a path, then we must now follow the path backward.
	 */
	while (index < curr->malloc_link)
	{
		link = curr->link[index];
		weight = link->one_two;
		to = link->room2;
		if (curr == link->room2)
		{
			weight = link->two_one;
			to = link->room1;
		}
		if (weight == -1)
		{
			/* check if the room is already visited in the path */
			if (is_visited(b, curr, to))
				return (NULL);
			/* If we are already following a path backward, then we are allowed to "jump off" to any neighbor.*/
			if (is_first_inverse_edge(b, curr))
				return (NULL);
			return (to);
		}
		index++;
	}
	return (NULL);
}

t_path *bfs(t_info *info)
{
	//printf("%s/*--------BFS START--------*/%s\n", PINK, WHITE);
	t_bfs b;
	t_path *path;
	t_room *curr;
	int index;

	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	while (b.head)
	{
		curr = pop(&(b.head));
		//printf("curr = %s\n", curr->room_name);
		index = 0;
		t_room *tmp = find_next_edge(&b, curr);
		if (tmp)
		{
			//printf("--- skip ---\n");
			push(&(b.tail), &(b.head), create(tmp));
			b.prev[tmp->index] = curr;
			b.visited[tmp->index] = TRUE;
		}
		else
		{
			while (index < curr->malloc_link)
			{
				bfs_condition(&b, curr, index);
				if (b.prev[info->end_room->index])
					break ;
			index++;
			}
		}
		//print_que(b.head, &b);
	}
	path = reverse_path(info, b.prev);
	free_que(b.head);
	free_bfs(&b);
	return (path);
}

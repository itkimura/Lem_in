/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/25 11:19:22 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_que	*pop(t_que **head)
{
	t_que	*new;

	if (!head || !(*head))
		return (NULL);
	new = *head;
	*head = (*head)->next;
	new->next = NULL;
	return (new);
}

void	push(t_que **tail, t_que **head, t_que *new)
{
	if (!tail)
		return ;
	if (*head == NULL)
	{
		*tail = new;
		*head = *tail;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_que	*mark_then_create(t_room *room, t_bool *visited)
{
	t_que	*new;

	new = (t_que *)malloc(sizeof(t_que));
	visited[room->index] = TRUE;
	if (new)
	{
		new->room = room;
		new->next = NULL;
	}
	return (new);
}

t_bool	get_path_len(t_info *info, t_room **prev, t_path *path)
{
	t_room	*tmp;

	tmp = info->end_room;
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

t_path	*reverse_path(t_info *info, t_room **prev)
{
	t_room	*tmp;
	t_path	*path;
	int		index;

	index = 0;
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
	print_path(path);
	return (path);
}

t_bool	init_bfs(t_info *info, t_bfs *b)
{
	int	index;

	index = 0;
	b->visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (b->visited == NULL)
		return (FALSE);
	ft_memset(b->visited, FALSE, sizeof(t_bool) * info->total_rooms);
	b->prev = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
	if (b->prev == NULL)
		return (FALSE);
	ft_memset(b->prev, 0, sizeof(t_room) * info->total_rooms);
	b->distance = (int *)malloc(sizeof(int) * info->total_rooms);
	if (b->distance == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		(b->distance)[index] = INT_MAX;
		index++;
	}
	b->head = mark_then_create(info->start_room, b->visited);
	b->tail = b->head;
	return (TRUE);
}

void	bfs_condition(t_bfs *b, t_room *curr, t_room **next, int index)
{
	int	weight;

	weight = curr->link[index]->one_two;
	*next = curr->link[index]->room2;
	if (curr->link[index]->room2 == curr)
	{
		weight = curr->link[index]->two_one;
		*next = curr->link[index]->room1;
	}
	if (b->visited[(*next)->index] == FALSE)
	{
		push(&(b->tail), &(b->head), mark_then_create((*next), b->visited));
		b->distance[(*next)->index] = b->distance[curr->index] + weight + 1;
		b->prev[(*next)->index] = curr;
	}
}

t_path	*bfs(t_info *info)
{
	t_bfs	b;
	t_room	*curr;
	t_room	*next;
	int		index;

	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	while (b.head)
	{
		curr = (pop(&(b.head)))->room;
		index = 0;
		while (index < curr->total_links)
		{
			bfs_condition(&b, curr, &next, index);
			if (next == info->end_room)
				return (reverse_path(info, b.prev));
			index++;
		}
	}
	return (NULL);
}

t_bool	get_paths(t_info *info)
{
	t_path	*path_curr;

	path_curr = bfs(info);
	// print_path(path_curr);
	return (TRUE);
}

t_bool	solution(t_info *info)
{
	printf("_____START BFS____\n");
	print_room(info->room_head);
	get_paths(info);
	return (TRUE);
}

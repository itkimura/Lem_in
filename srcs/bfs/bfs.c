/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/09 14:58:41 by thle             ###   ########.fr       */
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

t_bool	bfs_condition(t_info *info, t_bfs *b, t_room *curr)
{
	int		weight;
	t_room	*next;
	int		index;

	index = 0;
	while (index < curr->malloc_link)
	{
		get_next_weight(curr->link[index], curr, &next, &weight);
		if (b->visited[next->index] == FALSE && weight != 1)
		{
			next->path_nb = curr->path_nb;
			if (curr == info->start_room)
				next->path_nb = index;
			if (push_and_update(b, curr, next, FALSE) == FALSE)
				return (FALSE);
		}
		if (b->prev[next->path_nb]->path[info->end_room->index])
			break ;
		index++;
	}
	return (TRUE);
}

t_bool	is_visited(t_bfs *b, t_room *curr, t_room *next)
{
	t_room	*tmp;

	tmp = curr;
	while (tmp != NULL)
	{
		tmp = b->prev[curr->path_nb]->path[tmp->index];
		if (tmp == next)
			return (TRUE);
	}
	return (FALSE);
}

/*
 * test if there are inverse edge to go
 *
 * If we can get to a vertex v which is used by a path,
 * but the predecessor was not in a path,
 * then we must now follow the path backward.
 *
 * e.g.
 *
 * g -> e & g -> k: g -> e is an inverse edge, so skip K
 * j -> g : is an inverse edge
 * g -> k & g -> e: used an inverse edge already
 * 					so we are allowed to "jump off" to any neighbor
 * e -> b : visited, so not going
 * check if the room is already visited in the path
 * If we are already following a path backward,
 * then we are allowed to "jump off" to any neighbor
*/
t_bool	find_next_edge(t_info *info, t_bfs *b, t_room *curr, t_room **next)
{
	int		index;
	int		weight;

	index = 0;
	while (index < curr->malloc_link)
	{
		get_next_weight(curr->link[index], curr, next, &weight);
		if (weight == INVERSE)
		{
			if (is_visited(b, curr, *next)
				|| b->prev[curr->path_nb]->inverse == TRUE)
				return (FALSE);
			(*next)->path_nb = curr->path_nb;
			if (curr == info->start_room)
				(*next)->path_nb = index;
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

t_bool	bfs(t_info *info, t_path **path, t_bool flag)
{
	t_bfs	b;
	t_room	*curr;
	t_room	*next;

	if (info->start_room->malloc_link < 1 || init_bfs(info, &b) == FALSE)
		return (FALSE);
	while (b.head && flag == TRUE)
	{
		curr = pop(&(b.head));
		if (find_next_edge(info, &b, curr, &next) == TRUE)
		{
			if (push_and_update(&b, curr, next, TRUE) == FALSE)
				flag = FALSE;
		}
		else if (flag == TRUE)
			bfs_condition(info, &b, curr);
		if (b.prev[info->end_room->path_nb]->path[info->end_room->index])
			break ;
	}
	if (flag == TRUE && reverse_path(info,
			b.prev[info->end_room->path_nb]->path, path) == FALSE)
		flag = FALSE;
	free_bfs(&b, info->start_room->malloc_link);
	return (flag);
}

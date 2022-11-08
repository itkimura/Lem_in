/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 14:00:59 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"


/*
1 -> is_visited
-1 ->make inverse edge available
0 -> not used yet
*/

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

void	bfs_condition(t_info *info, t_bfs *b, t_room *curr)
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
			push(&(b->tail), &(b->head), create(next));
			b->prev[next->path_nb]->path[next->index] = curr;
			b->visited[next->index] = TRUE;
		}
		if (b->prev[next->path_nb]->path[info->end_room->index])
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
 * but the predecessor was not in a path, then we must now follow the path backward.
 *
 * e.g.
 *
 * g -> e & g -> k: g -> e is an inverse edge, so skip K
 * j -> g : is an inverse edge
 * g -> k & g -> e: used an inverse edge already so we are allowed to "jump off" to any neighbor
 * e -> b : visited, so not going
 */
/* check if the room is already visited in the path */
/* If we are already following a path backward, then we are allowed to "jump off" to any neighbor.*/

t_bool	find_next_edge(t_info *info, t_bfs *b, t_room *curr)
{
	int		index;
	int		weight;
	t_room	*next;

	index = 0;
	while (index < curr->malloc_link)
	{
		get_next_weight(curr->link[index], curr, &next, &weight);
		if (weight == INVERSE)
		{
			if (is_visited(b, curr, next)
				|| b->prev[curr->path_nb]->inverse == TRUE)
				return (FALSE);
			next->path_nb = curr->path_nb;
			if (curr == info->start_room)
				next->path_nb = index;
			push(&(b->tail), &(b->head), create(next));
			b->prev[next->path_nb]->path[next->index] = curr;
			b->prev[curr->path_nb]->inverse = TRUE;
			b->visited[next->index] = TRUE;
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

t_bool bfs(t_info *info, t_path **path)
{
	t_bfs	b;
	t_room	*curr;

	if (init_bfs(info, &b) == FALSE)
		return (FALSE);
	while (b.head)
	{
		curr = pop(&(b.head));
		if (find_next_edge(info, &b, curr) == FALSE)
			bfs_condition(info, &b, curr);
		if (b.prev[info->end_room->path_nb]->path[info->end_room->index])
			break ;
	}
	if(reverse_path(info, b.prev[info->end_room->path_nb]->path, path) == FALSE)
	{
		free_bfs(&b, info->start_room->malloc_link);
		return FALSE;
	}
	free_bfs(&b, info->start_room->malloc_link);
	return (TRUE);
}

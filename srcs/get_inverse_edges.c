/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inverse_edges.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:57:11 by thule             #+#    #+#             */
/*   Updated: 2022/11/02 16:40:22 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_dir get_flag_gie_condition(t_bfs *b, t_room *curr, t_room *next)
{
	// || (curr->splitted == FALSE && next->splitted == TRUE && b->table[next->index].visited[IN] == TRUE && b->table[next->index].visited[OUT] == FALSE)
	if ((next->splitted == FALSE && b->table[next->index].visited[OUT] == FALSE)
			|| (curr->splitted == TRUE && next->splitted == TRUE
				&& b->table[next->index].visited[OUT] == FALSE))
		return OUT;
	else if (!(b->table[next->index].visited[OUT] == TRUE && b->table[next->index].visited[IN] == FALSE) && next->splitted == TRUE && curr->splitted == FALSE && b->table[next->index].visited[IN] == FALSE)
		return IN;
	return NONE;
}

void get_weight_and_next(int *weight, t_room *curr, t_room **next, t_link *link)
{
	*weight = link->one_two;
	*next = link->room2;
	if (link->room2 == curr)
	{
		*weight = link->two_one;
		*next = link->room1;
	}
}

t_bool set_gie_condition(t_bfs *b, t_room *curr, t_room *next, int alt)
{
	t_dir dir;
	t_que *que;

	dir = get_flag_gie_condition(b, curr, next);
	if (dir > IN)
		return (TRUE);
	b->table[next->index].visited[dir] = TRUE;
	if (alt < b->table[next->index].distance[dir])
	{
		b->table[next->index].distance[dir] = alt;
		b->table[next->index].prev[dir] = curr;
	}
	que = create(next, b->table[next->index].distance[dir], dir);
	if (que == NULL)
		return FALSE;
	push(&(b->tail), &(b->head), que);
	return TRUE;
}

t_bool	gie_check_links(t_bfs *b, t_room *curr, int dir)
{
	t_room	*next;
	int		index;
	int		weight;

	index = 0;
	weight = 0;
	next = NULL;
	while (index < curr->malloc_link)
	{
		get_weight_and_next(&weight, curr, &next, curr->link[index]);
		if (!(weight == USED_INVERSE || weight == SKIP
			|| (dir == IN && weight != INVERSE)))
		{
			if (set_gie_condition(b, curr, next, b->table[curr->index].distance[dir] + weight) == FALSE)
				return (FALSE);
		}
		index++;
	}
	return (TRUE);
}

t_bool get_inverse_edges(t_info *info, t_path **path)
{
	t_bfs b;
	t_que *curr;

	if (init_bfs(info, &b) == FALSE)
		return (FALSE);
	while (b.head && b.table[info->end_room->index].visited[OUT] == FALSE)
	{
		curr = pop(&(b.head));
		if (gie_check_links(&b, curr->room, curr->dir) == FALSE)
		{
			free(curr);
			free(b.table);
			free_que(b.head);
			return (FALSE);
		}
		free(curr);
	}
	*path = reverse_path_test(info, b.table);
	free(b.table);
	free_que(b.head);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inversed_edges.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:57:11 by thule             #+#    #+#             */
/*   Updated: 2022/11/02 15:57:49 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_dir get_flag_gie_condition(t_bfs *b, t_room *curr, t_room *next)
{
	// || (curr->splitted == FALSE && next->splitted == TRUE && b->table[next->index].visited[IN] == TRUE && b->table[next->index].visited[OUT] == FALSE)
	if ((next->splitted == FALSE && b->table[next->index].visited[OUT] == FALSE) || (curr->splitted == TRUE && next->splitted == TRUE && b->table[next->index].visited[OUT] == FALSE))
		return OUT;
	else if (!(b->table[next->index].visited[OUT] == TRUE && b->table[next->index].visited[IN] == FALSE) && next->splitted == TRUE && curr->splitted == FALSE && b->table[next->index].visited[IN] == FALSE)
		return IN;
	return NONE;
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

t_path *get_inversed_edges(t_info *info)
{
	t_bfs b;
	t_que *curr;
	int index;
	int weight;
	t_room *next;

	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	while (b.head && b.table[info->end_room->index].visited[OUT] == FALSE)
	{
		curr = pop_test(&(b.head));
		index = -1;
		while (++index < curr->room->malloc_link)
		{
			get_weight_and_next(&weight, curr->room, &next, curr->room->link[index]);
			if (!(weight == USED_INVERSE || weight == SKIP || (curr->dir == IN && weight != INVERSE)))
			{
				if (set_gie_condition(&b, curr->room, next, b.table[curr->room->index].distance[curr->dir] + weight) == FALSE)
					exit(1);
			}
		}
	}
	return (reverse_path_test(info, b.table));
}

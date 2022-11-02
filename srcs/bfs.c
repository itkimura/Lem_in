/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:38:44 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/02 18:43:26 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool bfs(t_info *info, t_path **path, t_bool *visited)
{
	t_bfs	b;
	t_que	*curr;
	t_room	*next;
	int		index;
	int		weight;
	int	i;

	index = 0;
	weight = NORMAL_WEIGHT;
	next = NULL;
	if (init_bfs(info, &b) == FALSE)
		return (FALSE);
	i = 0;
	while (b.head && b.table[info->end_room->index].visited[OUT] == FALSE)
	{
		curr = pop(&(b.head));
		index = 0;
		while (index < curr->room->malloc_link)
		{
			if (!(curr->room->link[index]->one_two < 0 && curr->room->link[index]->two_one < 0))
			{
				get_weight_and_next(&weight, curr->room, &next, curr->room->link[index]);
				weight = NORMAL_WEIGHT;
				if (visited[next->index] == TRUE || b.table[next->index].visited[OUT] == TRUE)
				{
					index++;
					continue ;
				}
				int alt =  b.table[curr->room->index].distance[OUT] + weight;
				b.table[next->index].visited[OUT] = TRUE;
				if (alt < b.table[next->index].distance[OUT])
				{
					b.table[next->index].distance[OUT] = alt;
					b.table[next->index].prev[OUT] = curr->room;
				}
				t_que *que = create(next, b.table[next->index].distance[OUT], OUT);
				if (que == NULL)
				{
					free(curr);
					free(b.table);
					free_que(b.head);
					return (FALSE);
				}
				push(&(b.tail), &(b.head), que);
			}
			index++;
		}
		free(curr);
		i++;
	}
	*path = reverse_path_test(info, b.table);
	free(b.table);
	free_que(b.head);
	return (TRUE);
}

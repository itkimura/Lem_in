/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:33:59 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 13:35:03 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* update one_two and two_one in link*/
static void	update_link_weight_condition(t_room *from, t_link *tmp, t_bool *flag)
{
	if (tmp->room1 == from)
	{
		tmp->one_two = DROP;
		if (tmp->two_one != DROP)
			tmp->two_one = INVERSE;
	}
	else
	{
		tmp->two_one = DROP;
		if (tmp->one_two != DROP)
			tmp->one_two = INVERSE;
	}
	if (tmp->two_one == DROP && tmp->one_two == DROP)
		*flag = TRUE;
}

/* update edge weight by paths */
t_bool	update_link_weight(t_info *info, t_path *head)
{
	t_link	*tmp;
	t_room	*from;
	t_room	*to;
	t_bool	flag;
	int		index;

	flag = FALSE;
	index = 0;
	while (index < head->len - 1)
	{
		from = head->path[index];
		to = head->path[index + 1];
		tmp = link_hash_table_lookup(info->link_hash_table,
				from->index, to->index, info->total_links * RATIO);
		update_link_weight_condition(from, tmp, &flag);
		index++;
	}
	return (flag);
}

void	init_unused_links(t_info *info, t_path *head)
{
	t_link	*tmp;
	t_room	*from;
	t_room	*to;
	int		index;
	
	while (head)
	{
		index = 0;
		while (index < head->len - 1)
		{
			from = head->path[index];
			to = head->path[index + 1];
			tmp = link_hash_table_lookup(info->link_hash_table,
				from->index, to->index, info->total_links * RATIO);
			if (!(tmp->one_two == DROP && tmp->two_one == DROP))
			{
				tmp->one_two = UNUSED;
				tmp->two_one = UNUSED;
			}
			index++;
		}
		head = head->next;
	}
}
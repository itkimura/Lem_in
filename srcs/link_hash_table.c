/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:41:53 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 11:29:03 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	create_link_hash_table(t_info *info, int size)
{
	int	index;

	info->link_hash_table = (t_link **)malloc(sizeof(t_link *) * size);
	if (info->hash_table == NULL)
		return (FALSE);
	index = 0;
	while (index < size)
	{
		info->link_hash_table[index] = NULL;
		index++;
	}
	return (TRUE);
}

t_link	*link_hash_table_lookup(t_link **link_hash_table, int index_1, int index_2, int size)
{
	t_link	*tmp;
	int		index;

	index = (index_1 + index_2) % size;
	tmp = link_hash_table[index];
	while (tmp)
	{
		if (tmp
			&& ((tmp->room1->index == index_1 && tmp->room2->index == index_2)
			||	(tmp->room1->index == index_2 && tmp->room2->index == index_1)))
			break ;
		tmp = tmp->link_hash_table_next;
	}
	return (tmp);
}

t_bool	link_hash_table_appending(t_info *info, t_link *list, int size)
{
	t_link	*tmp;
	int		hash_value;

	hash_value = (list->room1->index + list->room2->index) % size;
	if (info->link_hash_table[hash_value] == NULL)
		info->link_hash_table[hash_value] = list;
	else
	{
		tmp = info->link_hash_table[hash_value];
		while (tmp)
		{
			if (tmp->link_hash_table_next == NULL)
				break ;
			tmp = tmp->link_hash_table_next;
		}
		tmp->link_hash_table_next = list;
	}
	return (TRUE);
}

t_bool	init_link_hash_table(t_info *info)
{
	t_link	*list;
	t_link	*next;
	int		size;

	size = info->total_links * RATIO;
	if (create_link_hash_table(info, size) == FALSE)
		return (FALSE);
	list = info->link_head;
	while (list)
	{
		next = list->next;
		if (link_hash_table_appending(info, list, size) == FALSE)
			return (FALSE);
		list = next;
	}
	return (TRUE);
}
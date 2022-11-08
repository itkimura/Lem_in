/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:45:20 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 17:56:39 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

unsigned int	hash(char *str, int size)
{
	unsigned int	hash_value;

	hash_value = 0;
	while (*str)
	{
		hash_value = ((hash_value * 97) + *str) % size;
		str++;
	}
	return (hash_value);
}

t_bool	create_room_hash_table(t_info *info)
{
	int	size;
	int	index;

	size = (int)(info->total_rooms * RATIO);
	info->hash_table = (t_room **)malloc(sizeof(t_room *) * size);
	if (info->hash_table == NULL)
		return (FALSE);
	index = 0;
	while (index < size)
	{
		info->hash_table[index] = NULL;
		index++;
	}
	return (TRUE);
}

t_room	*room_hash_table_lookup(t_room **hash_table, char *str, int size)
{
	t_room	*tmp;
	int		index;

	index = hash(str, size);
	tmp = hash_table[index];
	while (tmp)
	{
		if (tmp && !ft_strcmp(tmp->room_name, str))
			break ;
		tmp = tmp->hash_table_next;
	}
	return (tmp);
}

t_bool	room_hash_table_appending(t_info *info, t_room *list)
{
	t_room	*tmp;
	int		hash_value;

	hash_value = hash(list->room_name, (int)(info->total_rooms * RATIO));
	if (info->hash_table[hash_value] == NULL)
		info->hash_table[hash_value] = list;
	else
	{
		tmp = info->hash_table[hash_value];
		while (tmp)
		{
			if (ft_strcmp(tmp->room_name, list->room_name) == 0)
				return (print_error("Duplicate room name.\n"), FALSE);
			if (tmp->hash_table_next == NULL)
				break ;
			tmp = tmp->hash_table_next;
		}
		tmp->hash_table_next = list;
	}
	return (TRUE);
}

t_bool	init_room_hash_table(t_info *info)
{
	t_room	*list;
	t_room	*next;

	if (create_room_hash_table(info) == FALSE)
		return (FALSE);
	list = info->room_head;
	while (list)
	{
		next = list->list_next;
		if (room_hash_table_appending(info, list) == FALSE)
			return (FALSE);
		list = next;
	}
	return (TRUE);
}

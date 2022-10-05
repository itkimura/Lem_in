/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:45:20 by thle              #+#    #+#             */
/*   Updated: 2022/10/05 11:16:58 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int hash(char *str, int size)
{
	int hash_value;

	hash_value = 0;
	while (*str)
	{
		hash_value += (*str - '0');
		str++;
	}
	return (hash_value % size);
}

t_bool create_hash_table(t_info *info)
{
	int index;

	index = 0;
	info->hash_table = (t_room **)malloc(sizeof(t_room *) * info->quantity_of_rooms);
	if (info->hash_table == NULL)
		return (FALSE);
	while (index < info->quantity_of_rooms)
	{
		info->hash_table[index] = NULL;
		index++;
	}
	return (TRUE);
}

t_room	*hash_table_lookup(t_room **hash_table, char *str, int size)
{
	t_room	*tmp;
	int		index;

	index = hash(str, size);
	tmp = hash_table[index];
	while (tmp)
	{
		if (tmp && !ft_strcmp(tmp->room_name, str))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_bool hash_table_appending(t_info *info, t_room *list)
{
	t_room *tmp;
	int hash_value;

	hash_value = hash(list->room_name, info->quantity_of_rooms);
	if (info->hash_table[hash_value] == NULL)
		info->hash_table[hash_value] = list;
	else
	{
		tmp = info->hash_table[hash_value];
		while (tmp)
		{
			if (ft_strcmp(tmp->room_name, list->room_name) == 0)
				return (error("Duplicate room name.\n"), FALSE);
			if (tmp->next == NULL)
				break;
			tmp = tmp->next;
		}
		tmp->next = list;
	}
	return (TRUE);
}

t_bool init_hash_table(t_info *info)
{
	t_room *list;
	t_room *next;

	print_room(info->room_head);
	if (create_hash_table(info) == FALSE)
		return (FALSE);
	list = info->room_head;
	while (list)
	{
		next = list->next;
		if (hash_table_appending(info, list) == FALSE)
			return FALSE;
		list->next = NULL;
		list = next;
	}
	print_hash_table(info);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:45:20 by thle              #+#    #+#             */
/*   Updated: 2022/10/07 11:17:16 by itkimura         ###   ########.fr       */
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

t_bool	create_hash_table(t_info *info)
{
	int	size;

	size = sizeof(t_room *) * (int)(info->quantity_of_rooms * RATIO);
	info->hash_table = (t_room **)malloc(size);
	if (info->hash_table == NULL)
		return (FALSE);
	ft_memset(info->hash_table, 0, size);
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
		tmp = tmp->hash_table_next;
	}
	return (tmp);
}

t_bool	hash_table_appending(t_info *info, t_room *list)
{
	t_room	*tmp;
	int		hash_value;

	hash_value = hash(list->room_name, (int)(info->quantity_of_rooms * RATIO));
	if (info->hash_table[hash_value] == NULL)
		info->hash_table[hash_value] = list;
	else
	{
		tmp = info->hash_table[hash_value];
		while (tmp)
		{
			if (ft_strcmp(tmp->room_name, list->room_name) == 0)
				return (error("Duplicate room name.\n"), FALSE);
			if (tmp->hash_table_next == NULL)
				break ;
			tmp = tmp->hash_table_next;
		}
		tmp->hash_table_next = list;
	}
	return (TRUE);
}

t_bool	init_hash_table(t_info *info)
{
	t_room	*list;
	t_room	*next;

	if (create_hash_table(info) == FALSE)
		return (FALSE);
	list = info->room_head;
	while (list)
	{
		next = list->list_next;
		if (hash_table_appending(info, list) == FALSE)
			return (FALSE);
		list = next;
	}
	return (TRUE);
}

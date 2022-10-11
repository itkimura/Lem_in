/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:18 by thle              #+#    #+#             */
/*   Updated: 2022/10/07 13:59:39 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool	get_room_in_link(t_link *new, t_room **hash_table, char *line, int size)
{
	char	*tmp;
	char	*room1;
	char	*room2;
	int		len;

	tmp = ft_strchr(line, '-');
	while (tmp)
	{
		len = tmp - line;
		room1 = ft_strsub(line, 0, len);
		room2 = line + len + 1;
		if (room1 == NULL)
			return (error("Malloc fails.\n"), FALSE);
		new->room1 = hash_table_lookup(hash_table, room1, size);
		new->room2 = hash_table_lookup(hash_table, room2, size);
		ft_strdel(&room1);
		if (new->room1 && new->room2)
		{
			new->room1->quantity_of_links++;
			new->room2->quantity_of_links++;
			return (TRUE);
		}
		tmp = ft_strchr(tmp + 1, '-');
	}
	return (error("No room found in links.\n"), FALSE);
}

t_bool	create_new_link(t_info *info)
{
	t_link			*new;
	static t_link	*tmp;
	int				size;

	new = (t_link *)malloc(sizeof(t_link));
	if (new == NULL)
		return (error("Malloc fails.\n"), FALSE);
	new->room1 = NULL;
	new->room2 = NULL;
	size = (int)(info->quantity_of_rooms * RATIO);
	if (get_room_in_link(new, info->hash_table, info->line, size) == FALSE)
		return (free(new), FALSE);

	if (info->link_head == NULL)
	{
		info->link_head = new;
		tmp = new;
	}
	else
		tmp->next = new;
	tmp = new;
	new->next = NULL;
	return (TRUE);
}

t_bool	get_links(t_info *info)
{
	if (create_new_link(info) == FALSE)
		return (FALSE);
	return (TRUE);
}

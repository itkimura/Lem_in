/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:18 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 16:22:15 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

t_bool get_room_in_link(t_link *new, t_room **hash_table, char *line, int size)
{
	char *tmp;
	char *room1;
	char *room2;
	int len;

	tmp = ft_strchr(line, '-');
	while (tmp)
	{
		len = tmp - line;
		room1 = ft_strsub(line, 0, len);
		room2 = line + len + 1;
		if (room1 == NULL)
			return (print_error("Malloc fails.\n"), FALSE);
		new->room1 = hash_table_lookup(hash_table, room1, size);
		new->room2 = hash_table_lookup(hash_table, room2, size);
		ft_strdel(&room1);
		if (new->room1 &&new->room2)
		{
			new->room1->total_links++;
			new->room2->total_links++;
			return (TRUE);
		}
		tmp = ft_strchr(tmp + 1, '-');
	}
	return (print_error("No room found in links.\n"), FALSE);
}

void	init_single_link(t_link *new)
{
	new->room1 = NULL;
	new->room2 = NULL;
	new->one_two = 0;
	new->two_one = 0;
	new->link_hash_table_next = NULL;
}
t_bool	create_new_link(t_info *info)
{
	t_link *new;
	static t_link *tmp;
	int size;

	new = (t_link *)malloc(sizeof(t_link));
	if (new == NULL)
		return (print_error("Malloc fails.\n"), FALSE);
	init_single_link(new);
	size = (int)(info->total_rooms * RATIO);
	if (get_room_in_link(new, info->hash_table, info->line, size) == FALSE)
		return (free(new), FALSE);
	info->total_links++;
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

t_bool get_links(t_info *info)
{
	if (create_new_link(info) == FALSE)
		return (FALSE);
	return (TRUE);
}

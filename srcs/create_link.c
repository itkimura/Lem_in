/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:18 by thle              #+#    #+#             */
/*   Updated: 2022/10/05 17:50:54 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool get_room_name_in_link(t_link *new, t_room **hash_table, char *line, int size)
{
	int len;
	char *tmp;

	tmp = ft_strchr(line, '-');
	new->room1 = NULL;
	new->room2 = NULL;
	while (1)
	{
		if (tmp == NULL)
			break;
		len = tmp - line;
		new->room1 = ft_strsub(line, 0, len);
		new->room2 = ft_strsub(line, len + 1, ft_strlen(line));
		if (hash_table_lookup(hash_table, new->room1, size)
			&& hash_table_lookup(hash_table, new->room2, size))
			break;
		ft_strdel(&(new->room1));
		ft_strdel(&(new->room2));
		tmp = ft_strchr(tmp + 1, '-');
	}
	if (new->room1 &&new->room2)
		return (TRUE);
	return (error("No room found.\n"), FALSE);
}

t_bool create_new_link(t_link **link, t_info *info)
{
	t_link *new;
	int len;

	len = 0;
	new = (t_link *)malloc(sizeof(t_link));
	link = NULL;
	if (new == NULL)
		return (error("Malloc fails.\n"), FALSE);
	return get_room_name_in_link(new, info->hash_table, info->line, (int)(info->quantity_of_rooms * 2));
}

t_bool get_links(t_info *info)
{
	static t_link *link;

	if (create_new_link(&link, info) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

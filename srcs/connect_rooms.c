/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:06:59 by itkimura          #+#    #+#             */
/*   Updated: 2022/10/07 10:52:06 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	create_link_array(t_info *info)
{
	t_link	*link;
	t_link	*next;
	int		index;

	link = info->link_head;
	while (link)
	{
		next = link->next;
		index = 0;
		while (index < link->room1->malloc_link)
		{
			if (link->room1->link[index] == link->room2)
				break ;
			index++;
		}
		if (index == link->room1->malloc_link
			&& link->room1->quantity_of_links != 0)
		{
			link->room1->link[link->room1->malloc_link++] = link->room2;
			link->room2->link[link->room2->malloc_link++] = link->room1;
		}
		free(link);
		link = next;
	}
}

t_bool	connect_rooms(t_info *info)
{
	t_room	*room;
	int		size;

	room = info->room_head;
	while (room)
	{
		size = sizeof(t_room *) * room->quantity_of_links;
		room->link = (t_room **)malloc(size);
		if (room->link == NULL)
			return (error("Malloc fails.\n"), FALSE);
		ft_memset(room->link, 0, size);
		room = room->list_next;
	}
	create_link_array(info);
	return (TRUE);
}

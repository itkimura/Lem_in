/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:06:59 by itkimura          #+#    #+#             */
/*   Updated: 2022/10/25 11:07:31 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	link_exist(t_link *link)
{
	int	index;

	index = 0;
	while (index < link->room1->malloc_link)
	{
		if (link->room1->link[index]->room1 == link->room2
			|| link->room1->link[index]->room2 == link->room2)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	create_link_array(t_info *info)
{
	t_link	*link;

	link = info->link_head;
	while (link)
	{
		if (link_exist(link) == TRUE)
		{
			link = link->next;
			continue ;
		}
		link->room1->link[link->room1->malloc_link++] = link;
		link->room2->link[link->room2->malloc_link++] = link;
		link = link->next;
	}
}

t_bool	connect_rooms(t_info *info)
{
	t_room	*room;
	int		size;

	room = info->room_head;
	while (room)
	{
		size = sizeof(t_link *) * room->total_links;
		room->link = (t_link **)malloc(size);
		if (room->link == NULL)
			return (error("Malloc fails.\n"), FALSE);
		ft_memset(room->link, 0, size);
		room = room->list_next;
	}
	create_link_array(info);
	return (TRUE);
}

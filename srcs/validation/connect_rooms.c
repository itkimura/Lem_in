/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:06:59 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/08 13:43:45 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool link_exist(t_link *link)
{
	int index;

	index = 0;
	while (index < link->room1->malloc_link)
	{
		if (link->room1->link[index]->room1 == link->room2 || link->room1->link[index]->room2 == link->room2)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void create_link_array(t_info *info)
{
	t_link *link;

	link = info->link_head;
	while (link)
	{
		if (link_exist(link) == TRUE)
		{
			link = link->next;
			continue;
		}
		link->room1->link[link->room1->malloc_link++] = link;
		link->room2->link[link->room2->malloc_link++] = link;
		link = link->next;
	}
}

void init_link(t_link **link, int total_links)
{
	int index;

	index = 0;
	while (index < total_links)
	{
		link[index] = 0;
		index++;
	}
}

t_bool connect_rooms(t_info *info)
{
	t_room *room;

	room = info->room_head;
	while (room)
	{
		room->link = (t_link **)malloc(sizeof(t_link *) * room->total_links);
		if (room->link == NULL)
			return (print_error("Malloc fails.\n"), FALSE);
		init_link(room->link, room->total_links);
		room = room->list_next;
	}
	create_link_array(info);
	return (TRUE);
}

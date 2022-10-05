/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:01:48 by thle              #+#    #+#             */
/*   Updated: 2022/10/05 14:07:13 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool create_new_room(t_room **room, t_info *info)
{
	t_room *new;
	char *room_name;

	room_name = get_room_name(info->line);
	if ((room_name && room_name[0] == 'L') || check_xy(info->line + ft_strlen(room_name)) == FALSE)
		return (error("Wrong format.\n"), FALSE);
	new = (t_room *)malloc(sizeof(t_room));
	if (new == NULL)
		return (error("Malloc fails.\n"), FALSE);
	new->room_name = room_name;
	new->next = NULL;
	if (*room == NULL)
	{
		*room = new;
		info->room_head = new;
	}
	else
	{
		(*room)->next = new;
		*room = new;
	}
	(*room)->index = (info->quantity_of_rooms)++;
	return (TRUE);
}

char *get_room_name(char *line)
{
	char *room_name;
	int len;

	len = 0;
	while (line[len] != ' ')
		len++;
	room_name = ft_strsub(line, 0, len);
	if (!room_name)
		exit(0);
	return (room_name);
}

t_bool get_rooms(t_info *info, int type)
{
	static int command;
	static t_room *room;

	if (type == ROOM && (create_new_room(&room, info) == FALSE))
		return (FALSE);
	if (command == START)
		info->start_room = room->room_name;
	if (command == END)
		info->end_room = room->room_name;
	command = type;
	return (TRUE);
}

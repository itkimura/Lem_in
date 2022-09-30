/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 21:11:02 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/* thu */
e_bool create_new_room(t_room **room, char *room_name, t_info *info)
{
	t_room *new;

	if (room_name && room_name[0] == 'L')
		return FALSE;
	new = (t_room *)malloc(sizeof(t_room));
	if (new == NULL)
		exit(1);
	new->room_name = room_name;
	new->next = NULL;
	if (*room == NULL)
	{
		*room = new;
		info->head = new;
	}
	else
	{
		(*room)->next = new;
		*room = new;
	}
	(info->quantity_of_rooms)++;
	return (TRUE);
}

/* number_of_ants > 0 */
e_bool is_positive(int nb)
{
	if (nb < 0)
		return FALSE;
	return TRUE;
}

int type_of_line(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	else if (str[0] == '#' && str[1] != '#')
		return (COMMENT);
	else if (str[0] == '#')
		return (COMMAND);
	else if (ft_strchr(str, '-') && ft_strchr(str, ' ') == NULL)
		return (LINK);
	return (ROOM);
}

char *get_room_name(char *line)
{
	int len;
	char *room_name;

	len = 0;
	while (line[len] != ' ')
		len++;
	room_name = ft_strsub(line, 0, len); // check strsub
	if (!room_name)						 // malloc fail
		exit(0);
	return (room_name);
}

/* for later uses */
// void free_room(t_room *head)
// {
// }


e_bool get_rooms(t_room **room, t_info *info)
{
	char *line;
	int gnl;
	int type;
	int command;

	line = NULL;
	gnl = 1;
	while (gnl)
	{
		gnl = get_next_line(FD, &line);
		// printf("%s\n", line);
		if (gnl == 0)
			break;
		if (gnl < 0)
			exit(1);
		type = type_of_line(line);
		// printf("%s %d\n", line, type);
		if (type == ROOM)
		{
			create_new_room(room, get_room_name(line), info);
			// printf("%s\n", room->room_name);
			if (check_xy(line + ft_strlen((*room)->room_name)) == FALSE)
				return FALSE;
		}
		if (command == START)
		{
			info->start_room = (*room)->room_name;
		}
		if (command == END)
			info->end_room = (*room)->room_name;
		command = type;
		free(line);
	}
	return TRUE;
}

e_bool get_ants(char *line, t_info *info , int type)
{
	long nb;
	int i;

	i = 0;
	// printf("%s", line);
	if (type == COMMENT) //&& type == COMMAND
		return (TRUE);
	if (type != ROOM)
		return (FALSE);
	while (line[i])
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (FALSE);
		i++;
	}
	nb = ft_atol(line);
	if (nb < INT_MIN || nb > INT_MAX)
		return (FALSE);
	info->quantity_of_ants = nb;
	return (TRUE);
}

void print_room(t_room *room)
{
	while (room)
	{
		printf("[%s] ", room->room_name);
		room = room->next;
	}
	printf("\n");
}

/* gnl + validation */
e_bool read_line(t_room *room, t_info *info)
{
	char *line;
	int type;
	int gnl;

	line = NULL;
	gnl = 1;
	while (gnl && info->quantity_of_ants == 0)
	{
		gnl = get_next_line(FD, &line);
		if (gnl < 0)
			exit(1); // if gnl fail
		type = type_of_line(line);
		if (get_ants(line, info, type) == FALSE)
			return (FALSE);
		free(line);
	}
	if (get_rooms(&room, info) == FALSE)
	{
		return (FALSE);
	}
	return TRUE;
}

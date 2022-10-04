/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/10/04 15:08:38 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

e_bool	create_new_room(t_room **room, t_info *info)
{
	t_room	*new;
	char	*room_name;

	room_name = get_room_name(info->line);
	if ((room_name && room_name[0] == 'L')
		|| check_xy(info->line + ft_strlen(room_name)) == FALSE)
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

e_bool	is_duplicate(t_info *info)
{
	t_room	*tmp;
	t_room	*next;

	next = info->room_head;;
	while (next)
	{
		tmp = next->next;
		while (tmp)
		{
			if (ft_strcmp(next->room_name, tmp->room_name) == 0)
				return (FALSE);
			tmp = tmp->next;
		}
		next = next->next;
	}
	return (TRUE);
}

int	type_of_line(char *str)
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

char	*get_room_name(char *line)
{
	char	*room_name;
	int		len;

	len = 0;
	while (line[len] != ' ')
		len++;
	room_name = ft_strsub(line, 0, len);
	if (!room_name)
		exit(0);
	return (room_name);
}

/*
void	modify_by_command(t_info *info, t_room *room, int command)
{
	if (command == START)
		info->start_room = room->room_name;
	if (command == END)
		info->end_room = room->room_name;
}

e_bool	get_rooms(t_info *info)
{
	t_room		*room;
	int			type;
	int			command;
	short int	gnl;

	room = NULL;
	gnl = 1;
	while (gnl)
	{
		gnl = get_next_line(FD, &(info->line));
		if (gnl == 0 || type == LINK)
			break ;
		if (gnl < 0)
			exit(1);
		type = type_of_line(info->line);
		if (type == ROOM && (create_new_room(&room, info) == FALSE))
			return (FALSE);
		modify_by_command(info, room, command);
		command = type;
		free(info->line);
	}
	return (TRUE);
}
*/

e_bool	get_rooms(t_info *info, int type, int *stage)
{
	static int	command;
	static t_room *room;

	if (type == LINK)
	{
		if (is_duplicate(info) == FALSE)
			return (FALSE);
		(*stage)++;
		return (TRUE);
	}
	if (type == ROOM && (create_new_room(&room, info) == FALSE))
		return (FALSE);
	if (command == START)
		info->start_room = room->room_name;
	if (command == END)
		info->end_room = room->room_name;
	command = type;
	return (TRUE);
}

e_bool	get_ants(t_info *info, int type, int *stage)
{
	long	nb;
	int		i;

	i = 0;
	if (type == COMMENT)
		return (TRUE);
	if (type != ROOM)
		return (FALSE);
	while (info->line[i])
	{
		if (!(info->line[i] >= '0' && info->line[i] <= '9'))
			return (error("Wrong format for ants.\n"), FALSE);
		i++;
	}
	nb = ft_atol(info->line);
	if (nb < INT_MIN || nb > INT_MAX)
		return (error("Quantity of ants is not an integer."), FALSE);
	info->quantity_of_ants = nb;
	(*stage)++;
	return (TRUE);
}

int		hash(char *str, int size)
{
	int	hash_value;

	hash_value = 0;
	while (*str)
	{
		hash_value += (*str - '0');
		str++;
	}
	return (hash_value % size);
}

e_bool	init_hashtable(t_info *info)
{
	t_room	*list;
	t_room	*next;
	t_room	*tmp;
	int		hash_value;

	print_room(info->room_head);
	info->hash_table = (t_room **)malloc(sizeof(t_room *) * info->quantity_of_rooms);
	if (info->hash_table == NULL)
		return (FALSE);
	list = info->room_head;
	while (list)
	{
		next = list->next;
		hash_value = hash(list->room_name, info->quantity_of_rooms);
		if (info->hash_table[hash_value] == NULL)
			info->hash_table[hash_value] = list;
		else
		{
			tmp = info->hash_table[hash_value];
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = list;
		}
		list->next = NULL;
		list = next;
	}
	/*
	for (int i = 0; i < info->quantity_of_rooms;i++)
	{
		if (info->hash_table[i] == NULL)
			printf("No room\n");
		else
		{
			printf("room_name = %s hash_value = %d\n", info->hash_table[i]->room_name, i);
			t_room *test = info->hash_table[i]->next;
			if (test != NULL)
			{
				while (test)
				{
					printf("room_name = %s hash_value = %d\n", test->room_name, i);
					test = test->next;
				}
			}
		}
	}
	*/
	return (TRUE);
}
e_bool	path_to_each_stage(t_info *info, int type, int *stage)
{
	if (*stage == 0)
	{
		if (get_ants(info, type, stage) == FALSE)
			return (FALSE);
	}
	else if (*stage == 1)
	{
		if (get_rooms(info, type, stage) == FALSE)
			return (FALSE);
	}
	/* to add get_links*/
	return (TRUE);
}

e_bool	read_line(t_info *info)
{
	int		type;
	int		stage;
	int		gnl;

	gnl = 1;
	stage = 0;
	while (gnl)
	{
		gnl = get_next_line(FD, &(info->line));
		type = type_of_line(info->line);
		if (path_to_each_stage(info, type, &stage) == FALSE)
			return (FALSE);
		if (gnl == 0)
			break ;
		if (gnl < 0)
			exit(1);
		free(info->line);
	}
	init_hashtable(info);
	return (TRUE);
}

/*
e_bool	read_line(t_info *info)
{
	int		type;
	int		gnl;

	gnl = 1;
	while (gnl && info->quantity_of_ants == 0)
	{
		gnl = get_next_line(FD, &(info->line));
		if (gnl < 0)
			exit(1);
		type = type_of_line(info->line);
		if (get_ants(info, type) == FALSE)
			return (FALSE);
		free(info->line);
	}
	if (get_rooms(info) == FALSE)
		return (FALSE);
	//link_rooms();
	return (TRUE);
}
*/

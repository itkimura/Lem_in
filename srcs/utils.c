/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/10/04 16:58:48 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void print_room(t_room *room)
{
	printf("--- room ---\n");
	if (room == NULL)
	{
		printf("No room left\n");
		return;
	}
	while (room)
	{
		printf("room_name:[%s]\tindex:[%d]\n", room->room_name, room->index);
		room = room->next;
	}
	printf("\n");
}

void print_info(t_info *info)
{
	printf("--- info ---\n");
	printf("quantity_of_ants: %d\n", info->quantity_of_ants);
	printf("quantity_of_rooms: %d\n", info->quantity_of_rooms);
	printf("start_room: %s\n", info->start_room);
	printf("end_room: %s\n", info->end_room);
}

void error(char *error)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0;37m", 2);
}

void free_rooms(t_room **head)
{
	t_room *next;
	t_room *current;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->room_name);
		free(current);
		current = next;
	}
	*head = NULL;
}

void print_hash_table(t_info *info)
{
	t_room *test = NULL;

	for (int i = 0; i < info->quantity_of_rooms; i++)
	{
		test = NULL;
		if (info->hash_table[i] == NULL)
			printf("No room\n");
		else
		{
			printf("room_name = %s hash_value = %d\n", info->hash_table[i]->room_name, i);
			test = info->hash_table[i]->next;
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
}

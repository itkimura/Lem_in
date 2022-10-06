/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/10/06 14:34:47 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void print_single_room(t_room *room)
{
	if (room == NULL)
	{
		printf("Room is not existed.\n");
		return;
	}
	printf("room_name:[%s]\tindex:[%d]\n", room->room_name, room->index);
}

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
		printf("room_name:[%10s]\t\tindex:[%d]\n", room->room_name, room->index);
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
	int dup = 0;

	for (int i = 0; i < info->quantity_of_rooms * RATIO; i++)
	{
		test = NULL;
		if (info->hash_table[i] == NULL)
		{
			printf("%s[%s%3d%s]-----------------------------%s\n", YELLOW, PINK, i, YELLOW, WHITE);
			printf("\t%sNO ROOM%s\n", RED, WHITE);
			printf("\n");
		}
		else
		{
			printf("%s[%s%3d%s]-----------------------------%s\n", YELLOW, PINK, i, YELLOW, WHITE);
			test = info->hash_table[i];
			printf("\t[%s]\n", test->room_name);
			printf("\t%s \\____%slinks:[%2d]\n", GREY, WHITE, test->quantity_of_links);
			printf("\n");
			test = info->hash_table[i]->next;
			if (test != NULL)
			{
				while (test)
				{
					printf("\t[%s]\n", test->room_name);
					printf("\t%s \\____%slinks:[%2d]\n", GREY, WHITE, test->quantity_of_links);
					printf("\n");
					dup++;
					test = test->next;
				}
			}
		}
	}
	printf("rooms: %d\n", info->quantity_of_rooms);
	printf("dup = %d\n", dup);
}

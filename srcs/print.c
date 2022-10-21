/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/10/21 16:12:06 by itkimura         ###   ########.fr       */
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
	printf("room_name:[%s]\tindex:[%d]\tlevel[%d]\n", room->room_name, room->index, room->level);
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
		printf("room_name:[%10s]\t\tindex:[%d]\tlevel[%d]\n", room->room_name, room->index, room->level);
		room = room->list_next;
	}
	printf("\n");
}

void print_info(t_info *info)
{
	printf("--- info ---\n");
	printf("total_ants: %d\n", info->total_ants);
	printf("total_rooms: %d\n", info->total_rooms);
	printf("start_room: %s\n", info->start_room->room_name);
	printf("end_room: %s\n", info->end_room->room_name);
}

void print_hash_table(t_info *info)
{
	t_room *test = NULL;
	int	size = info->total_rooms * RATIO;
	int dup = 0;

	for (int i = 0; i < size ; i++)
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
			printf("\t%s \\____%smalloc_link:[%2d]\n", GREY, WHITE, test->malloc_link);
			printf("\t%s      %slinks:[", GREY, WHITE);
			for (int j = 0; j < test->malloc_link; j++)
				printf("%s ", test->link[j]->room_name);
			printf("]\n");
			test = info->hash_table[i]->hash_table_next;
			if (test != NULL)
			{
				while (test)
				{
					printf("\t[%s]\n", test->room_name);
					printf("\t%s \\____%slinks:[%2d]\n", GREY, WHITE, test->malloc_link);
					printf("\t%s      %slinks:[", GREY, WHITE);
					for (int j = 0; j < test->malloc_link; j++)
						printf("%s ", test->link[j]->room_name);
					printf("]\n");
					printf("\n");
					dup++;
					test = test->hash_table_next;
				}
			}
		}
	}
	printf("rooms: %d\n", info->total_rooms);
	printf("dup = %d\n", dup);
}

void	print_buff(t_path **buff)
{
	printf("---- buff ----\n");
	for (int i = 0; buff[i]->len ; i++)
	{
		printf("buff[%d]	%d:", i, buff[i]->len);
		for (int j = 0; j < buff[i]->len; j++)
			printf("%s ", buff[i]->path[j]->room_name);
		printf("\n");
	}
	
}

void	print_path(t_path	*path)
{
	for (int i = 0; i < path->len; i++)
		printf("[%s]", path->path[i]->room_name);

	printf("\n");
}

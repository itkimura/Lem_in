/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/11/03 22:58:09 by itkimura         ###   ########.fr       */
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

void print_rooms(t_room *room)
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
	int size = info->total_rooms * RATIO;
	int dup = 0;

	for (int i = 0; i < size; i++)
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
			{
				if (test->link[j] != NULL)
				{
					printf("ROOM1:%s ", test->link[j]->room1->room_name);
					printf("ROOM2:%s ", test->link[j]->room2->room_name);
					printf("one_two: %d | two_one%d\n", test->link[j]->one_two, test->link[j]->two_one);
				}
				else
				{
					printf("NULL");
				}
			}
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
					{
						if (test->link[j] != NULL)
						{
							printf("ROOM1:%s ", test->link[j]->room1->room_name);
							printf("ROOM2:%s ", test->link[j]->room2->room_name);
							printf("one_two: %d | two_one%d\n", test->link[j]->one_two, test->link[j]->two_one);
						}
						else
						{
							printf("NULL");
						}
					}
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

void print_buff(t_path **buff)
{
	printf("---- buff ----\n");
	for (int i = 0; buff[i]->len; i++)
	{
		printf("buff[%d]	%d:", i, buff[i]->len);
		for (int j = 0; j < buff[i]->len; j++)
			printf("%s ", buff[i]->path[j]->room_name);
		printf("\n");
	}
}

void print_single_path(t_path *path)
{
	if (path == NULL)
		printf("No path\n");
	else
	{
		printf("len:%d\t", path->len);
		for (int i = 0; i < path->len; i++)
			printf("[%s]", path->path[i]->room_name);
	}
	printf("\n");
}

void	print_paths(t_path *path)
{
	int	index;

	index = 0;
	while (path)
	{
		printf("No.%3d ", index);
		print_single_path(path);
		path = path->next;
		index++;
	}
}

void	print_single_link(t_link *link)
{
	printf("room1 = %s, room2 = %s, one_two = %d, two_one = %d\n", link->room1->room_name, link->room2->room_name, link->one_two, link->two_one);
}

void	print_links(t_info *info)
{
	t_link	*tmp;

	tmp = info->link_head;
	while (tmp)
	{
		print_single_link(tmp);
		tmp = tmp->next;
	}
}

char room_name_index(int index)
{
	char *str = "abcdefghijklmn";
	return str[index];
}

void printing_bfs(t_info *info, t_bfs *b)
{
	//printf("i\troom\tprev\tdist\n");
	//printf("i\tvisited\tprev\tdist\n");
	printf("i\tvisited\tprev\n");
	for(int index = 0; index < info->total_rooms; index++)
	{
		printf("%d\t", index);
		printf("%d\t", b->visited[index]);
		printf("%c\t", room_name_index(index));
		if (b->prev[index])
			printf("%s\t", b->prev[index]->room_name);
		else
			printf("(null)\t");
	}
}

void print_que(t_que *head, t_bfs *b)
{
	int index;

	index = 0;
	while (head)
	{
		printf("que[%d] = %s b->visited = %d\n", index, head->room->room_name, b->visited[head->room->index]);
		head = head->next;
		index++;
	}
	printf("\n");
}

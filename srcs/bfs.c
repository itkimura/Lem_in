/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/12 16:12:01 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int g_size;

t_bool init_buff(t_path ***buff, t_info *info)
{
	int index;

	index = 0;
	//	printf("size = %d\n", PATH_BUFF_SIZE);
	*buff = (t_path **)malloc(sizeof(t_path *) * PATH_BUFF_SIZE);
	if (buff == NULL)
		return (FALSE);
	while (index < PATH_BUFF_SIZE)
	{
		(*buff)[index] = (t_path *)malloc(sizeof(t_path));
		if ((*buff)[index] == NULL)
			return (FALSE);
		(*buff)[index]->path = (t_room **)malloc(sizeof(t_room *) * info->quantity_of_rooms);
		if ((*buff)[index]->path == NULL)
			return (FALSE);
		(*buff)[index]->len = 0;
		index++;
	}
	return (TRUE);
}

/* return the current position */
t_room *top(t_path *path)
{
	return (path->path[path->len - 1]);
}

t_bool visited(t_path *path, t_room *room)
{
	int index;

	index = 0;
	(void)room;
	while (index < path->len)
	{
		if (path->path[index] == room)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void init_queue(t_path **buff, t_room *start_room)
{
	buff[0]->path[0] = start_room;
	buff[0]->len = 1;
}

t_path *dep(t_path **buff, int *front)
{
	return (buff[(*front)++]);
}

t_bool extend_buffer(t_path ***buff, int *rear, t_info *info)
{
	t_path **tmp;
	int index;
	static int tmp_nb;
	static int constance;

	index = 0;
	if (tmp_nb == *rear)
		return (TRUE);
	tmp_nb = *rear;
	constance++;
	tmp = (t_path **)malloc(sizeof(t_path *) * ((constance + 1) * PATH_BUFF_SIZE));
	//	printf("rear = %d\n", *rear);
	while (index < *rear)
	{
		// printf("tmp = %p\n", tmp[index]);
		tmp[index] = (*buff)[index];
		//	printf("tmp = %p\n", tmp[index]);
		// printf("buff[%d]  = ", index);
		//		print_path(tmp[index]);
		index++;
	}
	// print_buff(tmp);
	// printf("index = %d\n", index);
	while (index < (constance + 1) * PATH_BUFF_SIZE)
	{
		tmp[index] = (t_path *)malloc(sizeof(t_path));
		if (tmp[index] == NULL)
			return (FALSE);

		tmp[index]->path = (t_room **)malloc(sizeof(t_room *) * info->quantity_of_rooms);
		if (tmp[index]->path == NULL)
			return (FALSE);
		tmp[index]->len = 0;
		index++;
	}
	// print_buff(tmp);
	//   printf("index = %d\n", index);
	free(*buff);
	*buff = tmp;
	//	printf("not fail\n");
	return (TRUE);
}

void enq(t_path **buff, t_path *tmp, t_room *next, int *rear)
{
	int index;

	index = 0;
	// print_path(tmp);
	// print_single_room(next);
	//	printf("rear: %d\n", *rear);
	// printf("buff[*rear]->path: %p\n", buff[*rear]->path);
	//	printf("ENQ:tmp->path = %p", tmp);
	// print_path(tmp);
	while (index < tmp->len)
	{
		//		printf("tmp->len = %d", tmp->len);
		//		print_path(tmp);
		buff[*rear]->path[index] = tmp->path[index];
		index++;
	}

	buff[*rear]->path[tmp->len] = next;
	buff[*rear]->len = tmp->len + 1;
	(*rear)++;
}

t_bool is_empty(int front, int rear)
{
	return (front == rear);
}

void free_buff(t_path **buff, int rear)
{
	int index;

	index = 0;
	while (index < ((rear + 99) / PATH_BUFF_SIZE) * PATH_BUFF_SIZE)
	{
		free(buff[index]->path);
		free(buff[index]);
		index++;
	}
	free(buff);
	buff = NULL;
}

void bfs_main(int *front, int *rear, t_room *end_room, t_path ***buff, t_info *info)
{
	t_path *tmp;
	t_room *curr;
	t_room *next;
	int index;

	index = 0;
	(void)end_room;
	while (is_empty(*front, *rear) == FALSE)
	{
		tmp = dep(*buff, front);
		curr = top(tmp);
		//	printf("1.DFS:tmp = %p\n", tmp);
		//	printf("tmp:");
		//	print_path(tmp);
		// printf("curr = %s\n", curr->room_name);
		if (curr == end_room)
		{
			// print_path(tmp);
		}
		else
		{
			index = 0;
			while (index < curr->quantity_of_links)
			{
				next = curr->link[index];
				if (visited(tmp, next) == FALSE)
				{
					if (*rear % PATH_BUFF_SIZE == 0)
					{
						extend_buffer(buff, rear, info);
						// tmp = buff[front - 1];
						//	printf("2.DFS:tmp = %p\n", tmp);
						//	print_path(tmp);
					}
					enq(*buff, tmp, next, rear);
				}
				index++;
			}
		}
	}
}

t_bool bfs(t_info *info)
{
	t_path **buff;
	t_room *start_room;
	t_room *end_room;
	int front;
	int rear;
	int size;

	buff = NULL;
	if (init_buff(&buff, info) == FALSE)
		return (FALSE);
	front = 0;
	rear = 1;
	size = info->quantity_of_rooms * RATIO;
	start_room = hash_table_lookup(info->hash_table, info->start_room, size);
	end_room = hash_table_lookup(info->hash_table, info->end_room, size);
	init_queue(buff, start_room);
	//print_info(info);
	bfs_main(&front, &rear, end_room, &buff, info);
	// print_buff(buff);
	// print_hash_table(info);
	
	free_buff(buff, rear);
	return (TRUE);
}

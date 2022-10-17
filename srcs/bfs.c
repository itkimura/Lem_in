/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/17 16:17:11 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool init_buff(t_path ***buff, t_info *info)
{
	int index;

	index = 0;
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
		(*buff)[index]->next = NULL;
		index++;
	}
	return (TRUE);
}

/* return the current position */
t_room *top(t_path *path)
{
	return (path->path[path->len - 1]);
}

t_bool visited(t_path *tmp, t_room *next, t_room *curr, t_room *end_room)
{
	int index;

	index = 0;
	while (index < tmp->len)
	{
		if (tmp->path[index] == next)
			return (TRUE);
		index++;
	}
	if (next == end_room)
		return (FALSE);
	if (next->level == 0)
		return (FALSE);
	if (next->level < curr->level)
		return (TRUE);
	if (next->index > curr->level)
		return (FALSE);
	if (next->level == curr->level)
	{
		index = 0;
		while (index < curr->quantity_of_links)
		{
			if (curr->link[index]->level == 0)
				return (TRUE);
			index++;
		}
		return (FALSE);
	}
	/*
	if (visited_array[next->index] < visited_array[curr->index])
		return (FALSE);
	if (visited_array[next->index] == 0)
		return (FALSE);
	if (curr->quantity_of_links == 2 && visited_array[next->index] == visited_array[curr->index])
		return (FALSE);
	*/
	return (TRUE);
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
	while (index < *rear)
	{
		tmp[index] = (*buff)[index];
		index++;
	}
	while (index < (constance + 1) * PATH_BUFF_SIZE)
	{
		tmp[index] = (t_path *)malloc(sizeof(t_path));
		if (tmp[index] == NULL)
			return (FALSE);
		tmp[index]->path = (t_room **)malloc(sizeof(t_room *) * info->quantity_of_rooms);
		if (tmp[index]->path == NULL)
			return (FALSE);
		tmp[index]->len = 0;
		tmp[index]->next = NULL;
		index++;
	}
	free(*buff);
	*buff = tmp;
	return (TRUE);
}

void enq(t_path **buff, t_path *tmp, t_room *next, int *rear)
{
	int index;

	index = 0;
	while (index < tmp->len)
	{
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

t_path *bfs_main(int *front, int *rear, t_path ***buff, t_info *info)
{
	t_path *tmp;
	t_room *curr;
	t_room *next;
	int index;

	while (is_empty(*front, *rear) == FALSE)
	{
		tmp = dep(*buff, front);
		curr = top(tmp);
		// printf("%d %d\n", *front, *rear);
		// print_path(tmp);
		print_buff(*buff);
		// printf("curr[%s] %d\n", curr->room_name, curr->level);
		if (curr == info->end_room)
			return (tmp);
		else
		{
			index = 0;
			while (index < curr->quantity_of_links)
			{
				next = curr->link[index];
				// printf("next[%s] %d\n", next->room_name, next->level);
				// printf("curr[%s] %d,\tnext[%s] %d\n", curr->room_name, curr->level, next->room_name, next->level);
				if (visited(tmp, next, curr, info->end_room) == FALSE)
				{
					if (*rear % PATH_BUFF_SIZE == 0)
						extend_buffer(buff, rear, info);
					enq(*buff, tmp, next, rear);
					if (next->level == 0)
						next->level = curr->level + 1;
					info->end_room->level++;
				}
				index++;
			}
		}
	}
	// printf("info->end_room->level: %d\n", info->end_room->level);
	return (NULL);
}

void print_path_list(t_path *tmp)
{
	int index;

	index = 0;
	while (tmp)
	{
		printf("path[%d]: ", index);
		print_path(tmp);
		index++;
		tmp = tmp->next;
	}
}

void print_flow(t_flow *tmp)
{
	int index;

	index = 0;
	while (tmp)
	{
		printf("flow[%d]: ", index);
		print_path(tmp->path);
		index++;
		tmp = tmp->next;
	}
}

t_flow *new_flow(t_path *path)
{
	t_flow *new;

	new = (t_flow *)malloc(sizeof(t_flow));
	if (new == NULL)
		return (NULL);
	new->path = path;
	new->next = NULL;
	return (new);
}

/*
t_bool	test_collision(t_path *head, t_path *curr, t_info *info)
{
	t_bool *visited;
	int		index;

	index = 1;
	visited = (t_bool *)malloc(sizeof(t_bool) * info->quantity_of_rooms);
	ft_memset(visited, FALSE, sizeof(t_bool) * info->quantity_of_rooms);
	while (curr)
	{
		while (index < curr->len)
		{

		}
		curr = curr->next;
	}
}

*/
void free_flow(t_flow *tmp)
{
	while (tmp)
	{
		free(tmp);
		tmp = tmp->next;
	}
}
/*

t_bool	test_flow(t_path *curr, t_path *head, t_info *info, t_flow **result, float *min)
{
	t_flow		*start;
	t_flow		*next;
	t_flow		*new;
	int			total;
	float			turn;

	start = new_flow(curr);
	next = start;
	total = 1;
	if (start == NULL)
		return (FALSE);
	while (head)
	{
		if (test_collision(head, start->path, info) && head != start->path)
		{
			new = new_flow(head);
			if (next == NULL)
				return (FALSE);
			next->next = new;
			next = new;
			total++;
		}
		head = head->next;
	}
	// printf("ants / how many path + longest length - 2 = %d\n", (info->quantity_of_ants / total) + (curr->len - 2));
	// print_flow(start);
	// printf("\n");
	turn = (info->quantity_of_ants / (float)total) + (curr->len - 2);
	printf("turn = %f\n", turn);
	if (*result == NULL)
	{
		*result = start;
		*min = turn;
	}
	else if (turn <= *min)
	{
//		free_flow(*result);
		*result = start;
		*min = turn;
	}
//	else
//		free_flow(*result);
	// if (*min < turn)
		// return (FALSE);
	return (TRUE);
}
*/

t_bool get_paths(int *front, int *rear, t_path ***buff, t_info *info)
{
	t_path *path_head;
	t_path *path_curr;
	t_path *path_next;
	t_flow *result;
	float min;
	int count_path;

	path_curr = bfs_main(front, rear, buff, info);
	path_head = path_curr;
	min = 0;
	// print_info(info);
	// printf("\n");
	count_path = 1;
	result = NULL;
	while (path_curr)
	{
		printf("\n[ test %d ]\n", count_path);
		print_path(path_curr);
		//		if (test_flow(path_curr, path_head, info, &result, &min) == FALSE)
		//			break ;
		print_path_list(path_head);
		(void)path_head;
		path_next = bfs_main(front, rear, buff, info);
		if (path_next == NULL)
			break;
		path_next->next = path_curr;
		path_curr = path_next;
		path_head = path_next;
		count_path++;
	}
	printf("%s", GREEN);
	printf("\n[ --- result --- ] min = %f\n", min);
	print_flow(result);
	printf("\n");
	printf("%s", WHITE);
	return (TRUE);
}

t_bool solution(t_info *info)
{
	t_path **buff;
	int front;
	int rear;

	buff = NULL;
	if (init_buff(&buff, info) == FALSE)
		return (FALSE);
	front = 0;
	rear = 1;
	init_queue(buff, info->start_room);
	get_paths(&front, &rear, &buff, info);
	// print_buff(buff);
	// print_hash_table(info);
	// print_room(info->room_head);
	free_buff(buff, rear);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/31 18:12:55 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* get path length */
t_bool get_path_len(t_info *info, t_room **prev, t_path *path)
{
	t_room *tmp;

	tmp = info->end_room;
	path->len = 0;
	while (tmp != NULL)
	{
		tmp = prev[tmp->index];
		path->len++;
	}
	path->path = (t_room **)malloc(sizeof(t_room *) * path->len);
	if (path->path == NULL)
		return (FALSE);
	return (TRUE);
}

/* get the path from prev[info->room] array in bfs */

t_path *reverse_path(t_info *info, t_room **prev)
{

	t_room *tmp;
	t_path *path;
	int index;

	index = 0;
	if (prev[info->end_room->index] == NULL)
		return (NULL);
	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);
	if (get_path_len(info, prev, path) == FALSE)
	{
		free(path);
		return (NULL);
	}
	index = path->len - 1;
	tmp = info->end_room;
	while (tmp)
	{
		path->path[index] = tmp;
		tmp = prev[tmp->index];
		index--;
	}
	path->next = NULL;
	return (path);
}

/*initiarize bfs struct */

t_bool init_bfs(t_info *info, t_bfs *b)
{
	int index;

	index = 0;
	b->prev = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
	if (b->prev == NULL)
		return (FALSE);
	ft_memset(b->prev, 0, sizeof(t_room *) * info->total_rooms);
	b->distance = (int *)malloc(sizeof(int) * info->total_rooms);
	if (b->distance == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		(b->distance)[index] = INT_MAX;
		index++;
	}
	b->distance[info->start_room->index] = 0;
	b->head = create(info->start_room);
	b->tail = b->head;
	return (TRUE);
}

void bfs_condition(t_bfs *b, t_room *curr, int index)
{
	int	weight;
	t_room *from;
	t_room *to;

	if (curr->link[index] == NULL)
		return ;
	weight = curr->link[index]->one_two;
	from = curr->link[index]->room1;
	to = curr->link[index]->room2;
	if (curr->link[index]->room2 == curr)
	{
		weight = curr->link[index]->two_one;
		from = curr->link[index]->room2;
		to = curr->link[index]->room1;
	}
	printf("from:%s to:%s weight = %d\n", from->room_name, to->room_name, weight);
	if (b->distance[from->index] != INT_MAX && b->distance[to->index] > b->distance[from->index] + weight)
	{
		push(&(b->tail), &(b->head), create(to));
		b->distance[to->index] = b->distance[from->index] + weight;
		b->prev[to->index] = curr;
	}
}

t_path *bfs(t_info *info)
{
	//printf("%s/*--------BFS START--------*/%s\n", PINK, WHITE);
	t_bfs b;
	t_path *path;
	t_room *curr;
	int index;

	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	t_link *tmp;
	tmp = info->link_head;
	while (tmp)
	{
		tmp = tmp->next;
	}
	while (b.head)
	{
		curr = pop(&(b.head));
		printf("curr = %s\n", curr->room_name);
		index = 0;
		while (index < curr->malloc_link)
		{
			bfs_condition(&b, curr, index);
			/*
			if (next == info->end_room)
			{
				printing_bfs(info, &b);
				path = reverse_path(info, b.prev);
				free_que(b.head);
				free_bfs(&b);
				return (path);
			}
			*/
			index++;
		}
		print_que(b.head, &b);
	}
	//printing_bfs(info, &b);
	path = reverse_path(info, b.prev);
	//print_rooms(info->room_head);
	//print_links(info);
	//printing_bfs(info, &b);
	print_single_path(path);
	//printf("%s/*--------BFS ENDS--------*/%s\n", PINK, WHITE);
	free_que(b.head);
	free_bfs(&b);
	return (path);
}

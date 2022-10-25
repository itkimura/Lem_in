/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/25 17:19:36 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void print_que(t_que *head)
{
	int index;

	index = 0;
	while (head)
	{
		printf("que[%d] = %s\n", index, head->room->room_name);
		head = head->next;
		index++;
	}
	printf("\n");
}

t_room *pop(t_que **head)
{
	t_que *tmp;
	t_room *room;

	if (!head || !(*head))
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	room = tmp->room;
	free(tmp);
	tmp = NULL;
	return (room);
}

void push(t_que **tail, t_que **head, t_que *new)
{
	if (!tail)
		return;
	if (*head == NULL)
	{
		*tail = new;
		*head = *tail;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_que *mark_then_create(t_room *room, t_bool *visited)
{
	t_que *new;

	new = (t_que *)malloc(sizeof(t_que));
	visited[room->index] = TRUE;
	if (new)
	{
		new->room = room;
		new->next = NULL;
	}
	return (new);
}

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
	return (path);
}

t_bool init_bfs(t_info *info, t_bfs *b)
{
	int index;

	index = 0;
	b->visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (b->visited == NULL)
		return (FALSE);
	ft_memset(b->visited, FALSE, sizeof(t_bool) * info->total_rooms);
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
	b->head = mark_then_create(info->start_room, b->visited);
	b->tail = b->head;
	return (TRUE);
}

void bfs_condition(t_bfs *b, t_room *curr, t_room **next, int index)
{
	int weight;

	if (curr->link[index] == NULL)
		return ;
	weight = curr->link[index]->one_two;
	*next = curr->link[index]->room2;
	if (curr->link[index]->room2 == curr)
	{
		weight = curr->link[index]->two_one;
		*next = curr->link[index]->room1;
	}
	if (b->visited[(*next)->index] == FALSE && b->distance[(*next)->index] > b->distance[curr->index] + weight)
	{
		// if (weight < 0)
		// {
		// 	push(&(b->tail), &(b->head), mark_then_create((*next), b->visited));
		// 	return ;
		// }
		push(&(b->tail), &(b->head), mark_then_create((*next), b->visited));
		b->distance[(*next)->index] = b->distance[curr->index] + weight;
		b->prev[(*next)->index] = curr;
	}
}

void free_bfs(t_bfs *b)
{
	free(b->visited);
	b->visited = NULL;
	free(b->prev);
	b->prev = NULL;
	free(b->distance);
	b->distance = NULL;
}

void free_path(t_path *path)
{
	free(path->path);
	free(path);
	path = NULL;
}

void free_que(t_que *head)
{
	t_que *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

char room_name_index(int index)
{
	char *str = "abcdefghijklmn";
	return str[index];
}

void printing_bfs(t_info *info, t_bfs *b)
{
	printf("i\tvisited\troom\tprev\tdist\n");
	// printf("i\tvisited\tprev\tdist\n");
	for(int index = 0; index < info->total_rooms; index++)
	{
		printf("%d\t", index);
		printf("%d\t", b->visited[index]);
		printf("%c\t", room_name_index(index));
		if (b->prev[index])
			printf("%s\t", b->prev[index]->room_name);
		else
			printf("(null)\t");
		printf("%d \n", b->distance[index]);
	}
}

t_path *bfs(t_info *info)
{
	printf("%s/*--------BFS START--------*/%s\n", PINK, WHITE);
	t_bfs b;
	t_path *path;
	t_room *curr;
	t_room *next;
	int index;

	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	while (b.head)
	{
		curr = pop(&(b.head));
		index = 0;
		while (index < curr->malloc_link)
		{
			bfs_condition(&b, curr, &next, index);
			// if (next == info->end_room)
			// {
			// 	printing_bfs(info, &b);
			// 	path = reverse_path(info, b.prev);
			// 	free_que(b.head);
			// 	free_bfs(&b);
			// 	printf("%s/*--------BFS ENDS--------*/%s\n", PINK, WHITE);
			// 	return (path);
			// }
			index++;
		}
	}
	printing_bfs(info, &b);
	path = reverse_path(info, b.prev);
	printf("%s/*--------BFS ENDS--------*/%s\n", PINK, WHITE);
	free_que(b.head);
	free_bfs(&b);
	return (path);
}

void drop_link(t_link *link, t_room *room)
{
	int index;

	index = 0;
	while (index < room->malloc_link)
	{
		if (room->link[index] == link)
		{
			room->link[index] = NULL;
			break;
		}
		index++;
	}
}

void update_link_weight(t_info *info, t_path *path)
{
	(void)info;
	int i;
	int j;
	t_room *curr;
	t_room *prev;

	i = path->len - 1;
	while (i > 0)
	{
		j = 0;
		curr = path->path[i];
		prev = path->path[i - 1];
		while (j < curr->malloc_link)
		{
			if (curr->link[j] != NULL && (prev == curr->link[j]->room1 || prev == curr->link[j]->room2))
			{
				if (prev == curr->link[j]->room1)
					curr->link[j]->two_one = -1;
				if (prev == curr->link[j]->room2)
					curr->link[j]->one_two = -1;
				drop_link(curr->link[j], prev);
			}
			j++;
		}
		i--;
	}
}

t_bool get_paths(t_info *info)
{
	t_path *path_curr;

	

	path_curr = bfs(info);
	while (path_curr)
	{
		update_link_weight(info, path_curr);
		print_path(path_curr);
		printf("\n");
		free_path(path_curr);
		path_curr = bfs(info);
	}
	print_path(path_curr);

	// path_curr = bfs(info);
	// if (path_curr)
	// 	update_link_weight(info, path_curr);
	// print_path(path_curr);
	// if (path_curr)
	// 	free_path(path_curr);

	// path_curr = bfs(info);
	// if (path_curr)
	// 	update_link_weight(info, path_curr);
	// print_path(path_curr);
	// if (path_curr)
	// 	free_path(path_curr);
	
	// path_curr = bfs(info);
	// if (path_curr)
	// 	update_link_weight(info, path_curr);
	// print_path(path_curr);
	// if (path_curr)
	// 	free_path(path_curr);

	return (TRUE);
}

t_bool solution(t_info *info)
{
	printf("_____START BFS____\n");
	print_room(info->room_head);
	get_paths(info);
	return (TRUE);
}

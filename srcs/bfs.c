/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/28 03:36:07 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void print_que(t_que *head)
{
	printf("start:\n");
	int index;

	index = 0;
	while (head)
	{
		printf("que[%d] = %s | weight: %d\n", index, head->room->room_name, head->weight);
		head = head->next;
		index++;
	}
	printf("end!\n\n");
	printf("\n");
}

t_room *pop(t_que **head)
{
	t_que *tmp;
	t_que *first;
	t_que *second;
	t_que *hold;

	if (!head || !(*head))
		return (NULL);
	tmp = *head;
	if (tmp->next == NULL)
	{
		*head = (*head)->next;
		return tmp->room;
	}
	hold = tmp;
	while (tmp && tmp->next)
	{
		if (hold->weight > tmp->next->weight)
		{
			first = tmp;
			hold = tmp->next;
			second = tmp->next->next;
		}
		tmp = tmp->next;
	}
	if (hold == *head)
	{
		*head = (*head)->next;
		return hold->room;
	}

	hold->next = NULL;
	first->next = second;
	return hold->room;
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

t_que *create(t_room *room, int weight)
{
	t_que *new;

	new = (t_que *)malloc(sizeof(t_que));
	if (new)
	{
		new->room = room;
		new->weight = weight;
		new->next = NULL;
	}
	return (new);
}

t_que *mark_then_create(t_room *room, int weight)
{
	t_que *new;

	new = (t_que *)malloc(sizeof(t_que));
	// visited[room->index] = TRUE;
	if (new)
	{
		new->room = room;
		new->weight = weight;
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
	b->head = mark_then_create(info->start_room, 0);
	b->tail = b->head;
	return (TRUE);
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
	for (int index = 0; index < info->total_rooms; index++)
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

void bfs_condition(t_bfs *b, t_room *curr, t_room **next, int index)
{
	int weight;

	if (curr->link[index] == NULL)
		return;
	weight = curr->link[index]->one_two;
	*next = curr->link[index]->room2;
	if (curr->link[index]->room2 == curr)
	{
		weight = curr->link[index]->two_one;
		*next = curr->link[index]->room1;
	}
	if (b->visited[(*next)->index] == FALSE)
	{
		push(&(b->tail), &(b->head), mark_then_create((*next), b->distance[curr->index] + weight));
		b->visited[(*next)->index] = TRUE;
		b->distance[(*next)->index] = b->distance[curr->index] + weight;
		b->prev[(*next)->index] = curr;
	}
}

t_path *bfs(t_info *info)
{
	// printf("%s/*--------BFS START--------*/%s\n", PINK, WHITE);
	t_bfs b;
	t_path *path;
	t_room *curr;
	t_room *next;
	int index;

	int count = 0;
	if (init_bfs(info, &b) == FALSE)
		return (NULL);
	b.visited[info->start_room->index] = TRUE;
	while (b.head && count < 10 && b.prev[info->end_room->index] == NULL)
	{
		curr = pop(&(b.head));
		index = 0;
		// printf("curr: %s\n", curr->room_name);
		while (index < curr->malloc_link)
		{
			bfs_condition(&b, curr, &next, index);
			index++;
		}
		// print_que(b.head);
		// count++;
	}

	// printing_bfs(info, &b);
	path = reverse_path(info, b.prev);
	// print_path(path);
	// printf("%s/*--------BFS ENDS--------*/%s\n", PINK, WHITE);
	// return NULL;
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
		// printf("curr: %s\n", curr->room_name);
		// printf("prev: %s\n", prev->room_name);
		if (i != 1 && i != path->len - 1)
		{
			curr->splitted = TRUE;
			prev->splitted = TRUE;
		}
		while (j < curr->malloc_link)
		{
			if (curr->link[j] != NULL && (prev == curr->link[j]->room1 || prev == curr->link[j]->room2))
			{
				if (prev == curr->link[j]->room1)
					curr->link[j]->two_one = 0;
				if (prev == curr->link[j]->room2)
					curr->link[j]->one_two = 0;
				drop_link(curr->link[j], prev);
				if (i == 1 || i == path->len - 1)
					drop_link(curr->link[j], curr);
			}
			j++;
		}
		i--;
	}
}

t_bool init_bfs_test(t_info *info, t_bfs *b)
{
	int index;

	index = 0;
	b->visited_test = (t_visited *)malloc(sizeof(t_visited) * info->total_rooms);
	if (b->visited_test == NULL)
		return (FALSE);
	ft_memset(b->visited_test, V_NOT, sizeof(t_bool) * info->total_rooms);

	b->table = (t_table *)malloc(sizeof(t_table) * info->total_rooms);

	if (b->table == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		b->table[index].distance[OUT] = INT_MAX;
		b->table[index].distance[IN] = INT_MAX;
		b->table[index].prev[OUT] = NULL;
		b->table[index].prev[IN] = NULL;
		index++;
	}
	return (TRUE);
}

char *get_name_test(int index)
{
	if (index == 0)
		return "3";
	else if (index == 1)
		return "start";
	else if (index == 2)
		return "end";
	else if (index == 3)
		return "4";
	else if (index == 4)
		return "1";
	else if (index == 5)
		return "2";
	else if (index == 6)
		return "5";
	else
		return "6";
}

void print_bfs_test(t_info *info, t_bfs *b)
{
	for(int index = 0; index < info->total_rooms; index++)
	{
		printf("%d\t", index);

		printf("%s\t", get_name_test(index));

		int visited_status = b->visited_test[index];
		if (visited_status == V_NOT)
			printf("V_NOT\t");
		else if (visited_status == V_OUT)
			printf("V_OUT\t");
		else if (visited_status == V_IN)
			printf("V_IN\t");
		else
			printf("V_BOTH\t");

		if (b->table[index].distance[OUT] == INT_MAX)
			printf("[OUT]: INF\t");
		else
			printf("[OUT]: %d\t", b->table[index].distance[OUT]);
			
		if (b->table[index].distance[IN] == INT_MAX)
			printf("[IN]: INF\n");
		else
			printf("[IN]: %d\n", b->table[index].distance[IN]);


		if (b->table[index].prev[OUT] == NULL)
			printf("\t\t\t[OUT]: NULL");
		else
			printf("\t\t\t[OUT]: %s", b->table[index].prev[OUT]->room_name);

		if (b->table[index].prev[IN] == NULL)
			printf("\t[IN]: NULL\n");
		else
			printf("\t[IN]: %s\n", b->table[index].prev[IN]->room_name);
		printf("\n");
	}
}

void bfs_test(t_info *info)
{

	t_bfs b;
	t_room *curr;
	int index;

	init_bfs_test(info, &b);

	b.head = create(info->start_room, 0);
	b.tail = b.head;
	b.visited_test[info->start_room->index] = V_OUT;
	b.table[info->start_room->index].distance[OUT] = 0;

	// print_bfs_test(info, &b);
	// print_que(b.head);
	while (b.head)
	{
		curr = pop(&(b.head));
		index = 0;
		while (index < curr->malloc_link)
		{
			if (curr->link[index] == NULL)
			{
				index++;
				continue;
			}
			int weight = curr->link[index]->one_two;
			t_room *next = curr->link[index]->room2;
			if (curr->link[index]->room2 == curr)
			{
				weight = curr->link[index]->two_one;
				next = curr->link[index]->room1;
			}
			if (next->splitted == FALSE && b.visited_test[next->index] == V_NOT)
			{
				push(&(b.tail), &(b.head), create(next, b.table[curr->index].distance[OUT] + weight));
				b.visited_test[next->index] = V_OUT;
				if (b.table[next->index].distance[OUT] > b.table[curr->index].distance[OUT] + weight)
				{
					b.table[next->index].distance[OUT] =  b.table[curr->index].distance[OUT] + weight;
					b.table[next->index].prev[OUT] = curr;
				}
			}
			if (next->splitted == TRUE && b.visited_test[next->index] != V_IN && b.visited_test[next->index] != V_BOTH)
			{
				// printf("weight: %d\n", weight);
				b.visited_test[next->index] = V_IN;
				b.table[next->index].distance[IN] =  b.table[curr->index].distance[OUT] + weight;
				b.table[next->index].prev[IN] = curr;
				for (int j = 0; j < next->malloc_link; j++)
				{
					t_room *next_in_line;
					if (next->link[j] != NULL && (next->link[j]->one_two == 0 || next->link[j]->two_one == 0))
					{
						push(&(b.tail), &(b.head), create(next_in_line, b.table[next->index].distance[IN]));
						next_in_line = next->link[j]->room1;
						if (next_in_line == next)
							next_in_line = next->link[j]->room2;
						b.visited_test[next_in_line->index] = V_OUT;
						b.table[next_in_line->index].distance[OUT] = b.table[next->index].distance[IN];
						b.table[next_in_line->index].prev[OUT] = next;
					}
				}
				printf("next: %s\n", next->room_name);
				printf("splitted\n");
				print_que(b.head);
				break;
			}
			printf("outside\n");
			print_que(b.head);
			index++;
		}
		print_bfs_test(info, &b);
		printf("----------------\n");
	}
	// print_bfs_test(info, &b);
}

t_bool get_paths(t_info *info)
{
	t_path *path_curr;
	// int count = 1;

	path_curr = bfs(info);
	update_link_weight(info, path_curr);
	// print_hash_table(info);
	// printf("\n\n");
	
	
	bfs_test(info);
	// while (path_curr)
	// {
	// 	update_link_weight(info, path_curr);
	// 	print_path(path_curr);
	// 	printf("\n");
	// 	free_path(path_curr);
	// 	print_hash_table(info);
	// 	// if (count == 2)
	// 	// 	break;
	// 	path_curr = bfs(info);
	// 	count++;
	// }
	// print_path(path_curr);

	return (TRUE);
}

t_bool solution(t_info *info)
{
	// printf("_____START BFS____\n");
	// print_room(info->room_head);

	get_paths(info);
	return (TRUE);
}

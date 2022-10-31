/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/31 19:51:34 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
augment_0.map gives 1 more line
prioritize inverse edge first in que
*/

void print_que(t_que *head)
{
	printf("start:\n");
	int index;

	index = 0;
	while (head)
	{
		if (head->direction == OUT)
			printf("que[%d] = %s | weight: %d | direction: OUT\n", index, head->room->room_name, head->weight);
		else
			printf("que[%d] = %s | weight: %d | direction: IN\n", index, head->room->room_name, head->weight);

		head = head->next;
		index++;
	}
	printf("end!\n\n");
	printf("\n");
}

t_que *pop_test(t_que **head)
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
		return tmp;
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
		return hold;
	}
	hold->next = NULL;
	first->next = second;
	return hold;
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

t_que *create(t_room *room, int weight, int direction)
{
	t_que *new;

	new = (t_que *)malloc(sizeof(t_que));
	if (new)
	{
		new->room = room;
		new->direction = direction;
		new->weight = weight;
		new->next = NULL;
	}
	return (new);
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
		if (i != 1 && i != path->len - 1)
		{
			curr->splitted = TRUE;
			prev->splitted = TRUE;
		}
		while (j < curr->malloc_link)
		{
			if (curr->link[j] != NULL && (prev == curr->link[j]->room1 || prev == curr->link[j]->room2))
			{
				if (curr->link[j]->one_two == INVERSE)
					curr->link[j]->one_two = USED_INVERSE;
				else if (curr->link[j]->two_one == INVERSE)
					curr->link[j]->two_one = USED_INVERSE;
				else
				{
					curr->link[j]->two_one = INVERSE;
					curr->link[j]->one_two = SKIP;
					if (prev == curr->link[j]->room2)
					{
						curr->link[j]->one_two = INVERSE;
						curr->link[j]->two_one = SKIP;
					}
				}
			}
			j++;
		}
		i--;
	}
}

t_path *reverse_path_test(t_info *info, t_table *table)
{
	t_room *curr = NULL;
	t_room *hold = NULL;
	t_path *path;
	int index;

	index = 0;
	curr = info->end_room;
	if (table[info->end_room->index].prev[OUT] == NULL)
		return (NULL);
	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);

	path->len = 0;
	while (curr != NULL)
	{
		if (hold != NULL && hold->splitted == FALSE && curr->splitted == TRUE)
		{
			hold = curr;
			if (table[curr->index].prev[OUT] && table[curr->index].prev[OUT]->splitted == TRUE)
				curr = table[curr->index].prev[OUT];
			else
				curr = table[curr->index].prev[IN];
		}
		else
		{
			hold = curr;
			if (table[curr->index].distance[IN] < table[curr->index].distance[OUT])
				curr = table[curr->index].prev[IN];
			else
				curr = table[curr->index].prev[OUT];
		}
		path->len++;
	}

	path->path = (t_room **)malloc(sizeof(t_room *) * path->len);
	if (path->path == NULL)
	{
		free(path);
		return NULL;
	}

	hold = NULL;
	index = path->len - 1;
	curr = info->end_room;
	while (curr)
	{
		path->path[index] = curr;
		if (hold != NULL && hold->splitted == FALSE && curr->splitted == TRUE)
		{
			hold = curr;
			if (table[curr->index].prev[OUT] && table[curr->index].prev[OUT]->splitted == TRUE)
				curr = table[curr->index].prev[OUT];
			else
				curr = table[curr->index].prev[IN];
		}
		else
		{
			hold = curr;
			if (table[curr->index].distance[IN] < table[curr->index].distance[OUT])
				curr = table[curr->index].prev[IN];
			else
				curr = table[curr->index].prev[OUT];
		}
		index--;
	}
	return path;
}

t_bool init_bfs_test(t_info *info, t_bfs *b)
{
	int index;

	index = 0;

	b->table = (t_table *)malloc(sizeof(t_table) * info->total_rooms);

	if (b->table == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		b->table[index].distance[OUT] = INT_MAX;
		b->table[index].distance[IN] = INT_MAX;
		b->table[index].prev[OUT] = NULL;
		b->table[index].prev[IN] = NULL;
		b->table[index].visited[OUT] = FALSE;
		b->table[index].visited[IN] = FALSE;
		index++;
	}
	return (TRUE);
}

char *get_name_test(int index)
{
	//test
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

	// augment_0.map
	// char *str = malloc(2);
	// str[1] = '\0';
	// if (index == 0)
	// 	return "s";
	// else if (index == 1)
	// 	return "end";
	// else
	// {
	// 	str[0] = index + 'a' - 2;
	// 	return str;
	// }
}

void print_bfs_test(t_info *info, t_bfs *b)
{
	for (int index = 0; index < info->total_rooms; index++)
	{
		printf("%d\t", index);

		printf("%s\t", get_name_test(index));
		// printf("%c\t", room_name_index(index));

		if (b->table[index].visited[OUT] == TRUE)
			printf("[OUT]: TRUE\t");
		else
			printf("[OUT]: FALSE\t");

		if (b->table[index].visited[IN] == TRUE)
			printf("[IN]: TRUE\n");
		else
			printf("[IN]: FALSE\n");

		if (b->table[index].distance[OUT] == INT_MAX)
			printf("\t\t[OUT]: INF\t");
		else
			printf("\t\t[OUT]: %d\t", b->table[index].distance[OUT]);

		if (b->table[index].distance[IN] == INT_MAX)
			printf("[IN]: INF\n");
		else
			printf("[IN]: %d\n", b->table[index].distance[IN]);

		if (b->table[index].prev[OUT] == NULL)
			printf("\t\t[OUT]: NULL");
		else
			printf("\t\t[OUT]: %s%s%s", GREEN, b->table[index].prev[OUT]->room_name, WHITE);

		if (b->table[index].prev[IN] == NULL)
			printf("\t[IN]: NULL\n");
		else
			printf("\t[IN]: %s%s%s\n", GREEN, b->table[index].prev[IN]->room_name, WHITE);
		printf("\n");
	}
}

t_path *bfs_test(t_info *info)
{

	t_bfs b;
	t_room *curr;
	t_que *curr_que;
	t_direction direction;
	int index;

	init_bfs_test(info, &b);

	b.head = create(info->start_room, 0, OUT);
	b.tail = b.head;
	b.table[info->start_room->index].visited[OUT] = TRUE;
	b.table[info->start_room->index].distance[OUT] = 0;

	int count = 0;
	while (b.head && b.table[info->end_room->index].visited[OUT] == FALSE)
	{
		curr_que = pop_test(&(b.head));
		curr = curr_que->room;
		direction = curr_que->direction;
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
			if (weight == USED_INVERSE || weight == SKIP)
			{
				index++;
				continue;
			}
			if (direction == IN && weight != INVERSE)
			{
				index++;
				continue;
			}
			if (next->splitted == FALSE && b.table[next->index].visited[OUT] == FALSE)
			{
				int alt = b.table[curr->index].distance[direction] + weight;
				b.table[next->index].visited[OUT] = TRUE;
				if (alt < b.table[next->index].distance[OUT])
				{
					b.table[next->index].distance[OUT] = alt;
					b.table[next->index].prev[OUT] = curr;
				}
				push(&(b.tail), &(b.head), create(next, b.table[next->index].distance[OUT], OUT));
			}
			else if (next->splitted == TRUE)
			{
				if (curr->splitted == FALSE)
				{
					if (b.table[next->index].visited[OUT] == TRUE && b.table[next->index].visited[IN] == FALSE)
					{
						index++;
						continue;
					}
					if (b.table[next->index].visited[IN] == FALSE)
					{
						int alt = b.table[curr->index].distance[direction] + weight;
						b.table[next->index].visited[IN] = TRUE;
						if (alt < b.table[next->index].distance[IN])
						{
							b.table[next->index].distance[IN] = alt;
							b.table[next->index].prev[IN] = curr;
						}
						push(&(b.tail), &(b.head), create(next, b.table[next->index].distance[IN], IN));
					}
					else if (b.table[next->index].visited[IN] == TRUE && b.table[next->index].visited[OUT] == FALSE)
					{
						int alt = b.table[curr->index].distance[direction] + weight;
						b.table[next->index].visited[OUT] = TRUE;
						if (alt < b.table[next->index].distance[OUT])
						{
							b.table[next->index].distance[OUT] = alt;
							b.table[next->index].prev[OUT] = curr;
						}
						push(&(b.tail), &(b.head), create(next, b.table[next->index].distance[OUT], OUT));
					}
				}
				else //next->splitted == TRUE && curr->splitted = TRUE
				{
					if (b.table[next->index].visited[OUT] == FALSE) // curr is splitted && next is splitted
					{
						// printf("curr: %s\n", curr->room_name);
						// printf("next: %s\n", next->room_name);
						int alt = b.table[curr->index].distance[direction] + weight;
						b.table[next->index].visited[OUT] = TRUE;
						if (alt < b.table[next->index].distance[OUT])
						{
							b.table[next->index].distance[OUT] = alt;
							b.table[next->index].prev[OUT] = curr;
						}
						push(&(b.tail), &(b.head), create(next, b.table[next->index].distance[OUT], OUT));
						// break;
					}
				}
			}
			// print_que(b.head);
		// print_bfs_test(info, &b);
		// printf("\n");
			index++;
		}
	}
	return reverse_path_test(info, b.table);
}

t_bool get_paths(t_info *info)
{
	t_path *path_curr;
	int count = 1;

	path_curr = bfs_test(info);
	printf("%s", BOLD);
	// printf("%d: ", count);
	print_path(path_curr);
	printf("%s", NORMAL);

	
	// while (path_curr)
	// {
	// 	update_link_weight(info, path_curr);
	// 	printf("%s", BOLD);
	// 	printf("%d: ", count);
	// 	print_path(path_curr);
	// 	printf("%s", NORMAL);
	// 	free_path(path_curr);
	// 	// print_hash_table(info);
	// 	// if (count == 2)
	// 	// 	break;
	// 	path_curr = bfs_test(info);
	// 	count++;
	// }
	// print_links(info);
	return (TRUE);
}

t_bool solution(t_info *info)
{
	// print_room(info->room_head);
	get_paths(info);
	return (TRUE);
}

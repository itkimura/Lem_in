/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/02 15:57:36 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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
		if (head->dir == OUT)
			printf("que[%d] = %s | weight: %d | dir: OUT\n", index, head->room->room_name, head->weight);
		else
			printf("que[%d] = %s | weight: %d | dir: IN\n", index, head->room->room_name, head->weight);

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

t_que *create(t_room *room, int weight, int dir)
{
	t_que *new;

	new = (t_que *)malloc(sizeof(t_que));
	if (new)
	{
		new->room = room;
		new->dir = dir;
		new->weight = weight;
		new->next = NULL;
	}
	return (new);
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
				if (curr->link[j]->one_two == INVERSE) // INVERSE = 0
					curr->link[j]->one_two = USED_INVERSE;
				else if (curr->link[j]->two_one == INVERSE)
					curr->link[j]->two_one = USED_INVERSE; // USED_INVERSE = -5
				else
				{
					curr->link[j]->two_one = INVERSE;
					curr->link[j]->one_two = SKIP; // -10
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

t_bool init_bfs(t_info *info, t_bfs *b)
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
	b->head = create(info->start_room, 0, OUT);
	if (b->head == NULL)
	{
		free(b->table);
		b->table = NULL;
		return (FALSE);
	}
	b->tail = b->head;
	b->table[info->start_room->index].visited[OUT] = TRUE;
	b->table[info->start_room->index].distance[OUT] = 0;
	return (TRUE);
}

char *get_name_test(int index)
{
	// test
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

void print_get_inverse_edges(t_info *info, t_bfs *b)
{
	for (int index = 0; index < info->total_rooms; index++)
	{
		printf("%d\t", index);

		// printf("%s\t", get_name_test(index));
		printf("%c\t", room_name_index(index));

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

void get_weight_and_next(int *weight, t_room *curr, t_room **next, t_link *link)
{
	*weight = link->one_two;
	*next = link->room2;
	if (link->room2 == curr)
	{
		*weight = link->two_one;
		*next = link->room1;
	}
}


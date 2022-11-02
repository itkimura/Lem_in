/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/02 17:27:58 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
augment_0.map gives 1 more line
prioritize inverse edge first in que
*/

t_que *pop(t_que **head)
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

t_bool update_link_weight(t_path *path)
{
	int		i;
	int		j;
	t_bool	res;
	t_room	*curr;
	t_room	*prev;

	i = path->len - 1;
	res = FALSE;
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
			if (prev == curr->link[j]->room1 || prev == curr->link[j]->room2)
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
			if (curr->link[j]->one_two < 0 && curr->link[j]->two_one < 0)
				res = TRUE;
			j++;
		}
		i--;
	}
	return (res);
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

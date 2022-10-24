/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/24 14:22:17 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_que *pop(t_que **head)
{
	t_que *new;
	if (!head || !(*head))
		return NULL;
	new = *head;
	*head = (*head)->next;
	new->next = NULL;
	return new;
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

t_que *create(t_room *room)
{
	t_que *new = (t_que *)malloc(sizeof(t_que));
	if (new)
	{
		new->room = room;
		new->next = NULL;
	}
	return new;
}

t_path *reverse_path(t_info *info, t_room **prev)
{
	t_room	*tmp;
	t_path	*path;
	int		index;

	for (int i = 0; i < info->total_rooms; i++)
	{
		if (prev[i])
			printf("prev[%d] = %s\n", i, prev[i]->room_name);
		else
			printf("prev[%d] = NULL\n", i);

	}
	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);
	path->len = 0;
	tmp = info->end_room;
	while (tmp != NULL)
	{
		tmp = prev[tmp->index];
		path->len++;
	}
	path->path = (t_room **)malloc(sizeof(t_room *) * path->len);
	if (path->path == NULL)
		return (NULL);
	index = path->len - 1;
	tmp = info->end_room;
	while (tmp)
	{
		path->path[index] = tmp;
		tmp = prev[tmp->index];
		index--;
	}
	print_path(path);
	return (path);
}

t_bool	init_bfs(t_info *info, t_bool **visited, int **distance, t_room ***prev)
{
	int	index;

	index = 0;
	*visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (*visited == NULL)
		return (FALSE);
	ft_memset(*visited, FALSE, sizeof(t_bool) * info->total_rooms);
	*prev = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
	if (*prev == NULL)
		return (FALSE);
	ft_memset(*prev, 0, sizeof(t_room) * info->total_rooms);
	*distance = (int *)malloc(sizeof(int) * info->total_rooms);
	if (*distance == NULL)
		return (FALSE);
	while (index < info->total_rooms)
	{
		(*distance)[index] = INT_MAX;
		index++;
	}
	return (TRUE);
}
t_path	*bfs(t_info *info)
{
	t_que	*head;
	t_que	*tail;
	t_room	*curr;
	t_room	*next;
	t_bool	*visited;
	int		weight;
	int		index;
	int		*distance;
	t_room	**prev;

	visited = NULL;;
	distance = NULL;;
	(void)tail;
	if (init_bfs(info, &visited, &distance, &prev) == FALSE)
		return (NULL);
	/*
	for (int i = 0; i < info->total_rooms; i++)
		printf("visited[%d] = %d\n", i, visited[i]);
	for (int i = 0; i < info->total_rooms; i++)
	{
		if (prev[i] == NULL)
			printf("prev[%d] = NULL\n", i);
		else
			printf("prev[%d] = %s\n", i, prev[i]->room_name);
	}
	for (int i = 0; i < info->total_rooms; i++)
		printf("distance[%d] = %d\n", i, distance[i]);
	*/
	head = create(info->start_room);
	tail = head;
	print_single_room(head->room);
	while (head)
	{
		curr = (pop(&head))->room;
		print_single_room(curr);
		index = 0;
		while (index < curr->total_links)
		{
			weight = curr->link[index]->one_two;
			next = curr->link[index]->room2;
			if (curr->link[index]->room2 == curr)
			{
				weight = curr->link[index]->two_one;
				next = curr->link[index]->room1;
			}
			printf("weight = %d\n", weight);
			print_single_room(next);
			
			if (visited[next->index] == FALSE)
			{
				push(&tail, &head, create(next));
				visited[next->index] = TRUE;
				distance[next->index] = distance[curr->index] + weight + 1;
				prev[next->index] = curr;
			}
			if (next == info->end_room)
				return (reverse_path(info, prev));
			index++;
		}
	}
	return (NULL);
}

t_bool	get_paths(t_info *info)
{
	t_path	*path_curr;

	path_curr = bfs(info);
	//print_path(path_curr);
	return (TRUE);
}

t_bool	solution(t_info *info)
{
	get_paths(info);
	return (TRUE);
}

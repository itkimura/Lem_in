/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/21 16:12:17 by itkimura         ###   ########.fr       */
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

t_path	*bfs(t_info *info, t_bool *visited)
{
	t_que	*head;
	t_que	*tail;
	t_room	**prev;
	t_room	*curr;
	int		index;

	prev = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
	if (prev == NULL)
		return (NULL);
	ft_memset(prev, FALSE, sizeof(t_room *) * info->total_rooms);
	visited[info->start_room->index] = TRUE;
	head = create(info->start_room);
	tail = head;
	while (head)
	{
		curr = (pop(&head))->room;
		index = 0;
		while (index < curr->total_links)
		{
			if (visited[curr->link[index]->index] == FALSE)
			{
				push(&tail, &head, create(curr->link[index]));
				visited[curr->link[index]->index] = TRUE;
				prev[curr->link[index]->index] = curr;
			}
			if (curr->link[index] == info->end_room)
				return (reverse_path(info, prev));
			index++;
		}
	}
	return (NULL);
}

t_bool	get_paths(t_info *info)
{
	t_path	*path_curr;
	int		count_path;
	t_bool	*visited;

	print_room(info->room_head);
	visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (visited == NULL)
		return (FALSE);
	ft_memset(visited, FALSE, sizeof(t_bool) * info->total_rooms);
	path_curr = bfs(info, visited);
	count_path = 1;
	for (int i = 0; i < info->total_rooms; i++)
		printf("visited[%d] = %d\n", i, visited[i]);
	/*
	while (path_curr)
	{
		path_curr = bfs(info, visited);
	}
	*/
	return (TRUE);
}

t_bool	solution(t_info *info)
{
	//get_paths(info);
	return (TRUE);
}

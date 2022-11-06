/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/06 11:46:55 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void free_bfs(t_bfs *b, int	malloc_link)
{
	int	index;

	index = 0;
	while (index < malloc_link)
	{
		free(b->prev[index]->path);
		free(b->prev[index]);
		index++;
	}
	free(b->visited);
	b->visited = NULL;
	free(b->prev);
	b->prev = NULL;
	free_que(b->head);
}

void free_path(t_path *path)
{
	free(path->path);
	free(path);
	path = NULL;
}

void free_paths(t_path *path)
{
	while (path)
	{
		free_path(path);
		path = path->next;
	}
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

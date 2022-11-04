/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/04 12:24:50 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void free_bfs(t_bfs *b)
{
	free(b->visited);
	b->visited = NULL;
	free(b->prev);
	b->prev = NULL;
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

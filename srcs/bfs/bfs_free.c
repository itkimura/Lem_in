/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 18:46:58 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_bfs(t_bfs *b, int malloc_link)
{
	int	index;

	index = 0;
	if (b->prev)
	{
		while (index < malloc_link)
		{
			if (b->prev[index])
			{
				free(b->prev[index]->path);
				free(b->prev[index]);
			}
			index++;
		}
		free(b->prev);
		b->prev = NULL;
	}
	if (b->visited)
	{
		free(b->visited);
		b->visited = NULL;
	}
	free_que(b->head);
}

void	free_path(t_path *path)
{
	free(path->path);
	free(path);
	path = NULL;
}

void	free_paths(t_path *path)
{
	while (path)
	{
		free_path(path);
		path = path->next;
	}
}

void	free_que(t_que *head)
{
	t_que	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

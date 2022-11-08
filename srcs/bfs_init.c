/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:27:18 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 10:29:24 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_path(t_room **path, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		path[index] = NULL;
		index++;
	}
}

t_bool	init_prev(t_info *info, t_bfs *b)
{
	int	index;

	index = 0;
	b->prev = (t_prev **)malloc(sizeof(t_prev *) * info->start_room->malloc_link);
	if (b->prev == NULL)
		return (FALSE);
	while (index < info->start_room->malloc_link)
	{
		b->prev[index] = (t_prev *)malloc(sizeof(t_path));
		if (b->prev[index] == NULL)
			return (FALSE);
		b->prev[index]->path = (t_room **)malloc(sizeof(t_room *) * info->total_rooms);
		if (b->prev[index]->path == NULL)
			return (FALSE);
		init_path(b->prev[index]->path, info->total_rooms);
		b->prev[index]->inverse = FALSE;
		index++;
	}
	return (TRUE);
}

void	init_visited(t_bool *visited, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		visited[index] = FALSE;
		index++;
	}
}

/*initiarize bfs struct */
t_bool	init_bfs(t_info *info, t_bfs *b)
{
	if (init_prev(info, b) == FALSE)
		return (FALSE);
	b->visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (b->visited == NULL)
		return (FALSE);
	init_visited(b->visited, info->total_rooms);
	b->head = create(info->start_room);
	b->tail = b->head;
	b->visited[info->start_room->index] = TRUE;
	return (TRUE);
}
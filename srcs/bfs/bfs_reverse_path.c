/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_reverse_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 15:33:57 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* get path length */
t_bool	get_path_len(t_info *info, t_room **prev, t_path *path)
{
	t_room	*tmp;

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

/* get the path from prev[info->room] array in bfs */
t_bool reverse_path(t_info *info, t_room **prev, t_path **path)
{
	t_room	*tmp;
	int		index;

	index = 0;
	if (prev[info->end_room->index] == NULL)
		return (TRUE);
	*path = (t_path *)malloc(sizeof(t_path));
	if (*path == NULL)
		return (FALSE);
	if (get_path_len(info, prev, *path) == FALSE)
	{
		free(*path);
		return (FALSE);
	}
	index = (*path)->len - 1;
	tmp = info->end_room;
	while (tmp)
	{
		(*path)->path[index] = tmp;
		tmp = prev[tmp->index];
		index--;
	}
	(*path)->next = NULL;
	return (TRUE);
}

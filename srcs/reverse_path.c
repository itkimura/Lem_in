/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:06:42 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/01 18:09:18 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	get_prev_room(t_table *table, t_room **hold, t_room **curr)
{
	if (*hold != NULL && (*hold)->splitted == FALSE && (*curr)->splitted == TRUE)
	{
		*hold = *curr;
		if (table[(*curr)->index].prev[OUT] && table[(*curr)->index].prev[OUT]->splitted == TRUE)
			*curr = table[(*curr)->index].prev[OUT];
		else
			*curr = table[(*curr)->index].prev[IN];
	}
	else
	{
		*hold = *curr;
		if (table[(*curr)->index].distance[IN] < table[(*curr)->index].distance[OUT])
			*curr = table[(*curr)->index].prev[IN];
		else
			*curr = table[(*curr)->index].prev[OUT];
	}
}

t_path	*malloc_path(int len)
{
	t_path *path;

	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (NULL);
	path->path = (t_room **)malloc(sizeof(t_room *) * len);
	if (path->path == NULL)
	{
		free(path);
		return (NULL);
	}
	path->len = len;
	path->next = NULL;
	return (path);
}

t_path	*reverse_path_test(t_info *info, t_table *table)
{
	t_room	*curr;
	t_room	*hold;
	t_path	*path;
	int		len;
	int index;

	if (table[info->end_room->index].prev[OUT] == NULL)
		return (NULL);
	curr = info->end_room;
	hold = NULL;
	len = 0;
	while (curr != NULL)
	{
		get_prev_room(table, &hold, &curr);
		len++;
	}
	path = malloc_path(len);
	if (path)
	{
		index = path->len - 1;
		hold = NULL;
		curr = info->end_room;
		while (curr)
		{
			//printf("curr = %s\n", curr->room_name);
			path->path[index] = curr;
			//if (curr == info->start_room)
			//	break ;
			//if (hold)
			//	printf("index = %d hold = %s curr = %s\n", index, hold->room_name, curr->room_name);
			get_prev_room(table, &hold, &curr);
			index--;
		}
	}
	return (path);
}

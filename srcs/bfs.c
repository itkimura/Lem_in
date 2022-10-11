/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/10 11:17:31 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool	init_buff(t_path ***buff, t_info *info)
{
	int	index;

	index = 0;
	*buff = (t_path **)malloc(sizeof(t_path *) * 100);
	if (buff == NULL)
		return (FALSE);
	while (index < 100)
	{
		(*buff)[index] = (t_path *)malloc(sizeof(t_path));
		if ((*buff)[index] == NULL)
			return (FALSE);
		(*buff)[index]->path = (t_room **)malloc
			(sizeof(t_room *) * info->quantity_of_rooms);
		if ((*buff)[index]->path == NULL)
			return (FALSE);
		(*buff)[index]->len = 0;
		index++;
	}
	return (TRUE);
}

/* return the current position */
t_room	*top(t_path	*path)
{
	return (path->path[path->len - 1]);
}

t_bool	visited(t_path *path, t_room *room)
{
	int	index;

	index = 0;
	(void)room;
	while (index < path->len)
	{
		if (path->path[index] == room)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	init_queue(t_path **buff, t_room *start_room)
{
	buff[0]->path[0] = start_room;
	buff[0]->len = 1;
}

t_path	*dep(t_path **buff, int *front)
{
	return (buff[(*front)++]);
}

void	enq(t_path **buff, t_path *tmp, t_room *next, int *end)
{
	int	index;

	(void)next;
	index = 0;
	while (index < tmp->len)
	{
		buff[*end]->path[index] = tmp->path[index];
		index++;
	}
	buff[*end]->path[tmp->len] = next;
	buff[*end]->len = tmp->len + 1;
	(*end)++;
}

t_bool	is_empty(int front, int rear)
{
	return (front == rear);
}

void	free_buff(t_path **buff, t_info *info)
{
	int	index;

	index = 0;
	(void)info;
	while (index < 100)
	{
		free(buff[index]->path);
		free(buff[index]);
		index++;
	}
	free(buff);
	buff = NULL;
}

void	bfs_main(int front, int rear, t_room *end_room, t_path **buff)
{
	t_path	*tmp;
	t_room	*curr;
	t_room	*next;
	int		index;

	index = 0;
	while (!is_empty(front, rear))
	{
		tmp = dep(buff, &front);
		curr = top(tmp);
		if (curr == end_room)
			print_path(tmp);
		else
		{
			index = 0;
			while (index < curr->quantity_of_links)
			{
				next = curr->link[index];
				if (visited(tmp, next) == FALSE)
					enq(buff, tmp, next, &rear);
				index++;
			}
		}
	}
}

t_bool	bfs(t_info *info)
{
	t_path	**buff;
	t_room	*start_room;
	t_room	*end_room;
	int		size;

	buff = NULL;
	if (init_buff(&buff, info) == FALSE)
		return (FALSE);
	size = info->quantity_of_rooms * RATIO;
	start_room = hash_table_lookup(info->hash_table, info->start_room, size);
	end_room = hash_table_lookup(info->hash_table, info->end_room, size);
	init_queue(buff, start_room);
	bfs_main(0, 1, end_room, buff);
	print_info(info);
	//print_buff(buff);
	//print_hash_table(info);
	free_buff(buff, info);
	return (TRUE);
}

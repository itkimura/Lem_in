/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:51:25 by thule             #+#    #+#             */
/*   Updated: 2022/11/05 17:21:41 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void print_ant_to_room(char *ant, char *room_name)
{
	write(1, "L", 1);
	ft_putstr(ant);
	write(1, "-", 1);
	ft_putstr(room_name);
	write(1, " ", 1);
}

void print_ants_helper(t_ants *ants, t_info *info, int *hold)
{
	int ant_order;
	t_ants curr_ant;
	t_path *path;

	ant_order = *hold;
	while (ant_order < info->total_ants)
	{
		curr_ant = ants[ant_order];
		path = curr_ant.path;
		if (curr_ant.pos > path->len - 1)
		{
			if (ant_order == *hold + 1)
				*hold = ant_order;
			info->end_room->is_occupied = FALSE;
		}
		else if (path->path[curr_ant.pos]->is_occupied == FALSE
				|| path->path[curr_ant.pos] == info->end_room)
		{
			print_ant_to_room(curr_ant.nbr, path->path[curr_ant.pos]->room_name);
			path->path[curr_ant.pos]->is_occupied = TRUE;
			if (curr_ant.pos > 1)
				path->path[curr_ant.pos - 1]->is_occupied = FALSE;
			ants[ant_order].pos = ants[ant_order].pos + 1;
		}
		ant_order++;
	}
}

void print_ants(t_result *result, t_ants *ants, t_info *info)
{
	int flow;
	int index;
	int hold;

	flow = result->min_turn;
	index = 0;
	hold = 0;
	while (index < flow)
	{
		print_ants_helper(ants, info, &hold);
		ft_putchar('\n');
		index++;
	}
}

t_bool set_ant_value(t_ants *ants, t_path *path, int index, int *ant_amount)
{
	ants[index].nbr = ft_itoa(index + 1);
	if (ants[index].nbr == NULL)
		return (FALSE);
	ants[index].path = path;
	ants[index].pos = 1;
	*ant_amount = *ant_amount - 1;
	return (TRUE);
}

t_bool assign_ants_order(t_result *result, t_ants *ants, int total_ants)
{
	t_path *path;
	int path_order;
	int index;

	path = result->best_paths;
	path_order = 0;
	index = -1;
	while (++index < total_ants)
	{
		if (path_order == result->total)
		{
			path = result->best_paths;
			path_order = 0;
		}
		if (result->divide_ants[path_order][1] <= 0)
			index--;
		else if (set_ant_value(ants, path, index,
							   &((result->divide_ants[path_order][1]))) == FALSE)
			return (FALSE);
		path = path->next;
		path_order++;
	}
	return (TRUE);
}

void free_ants(t_ants **ants, int total_ants)
{
	int index;

	index = 0;
	while (index < total_ants)
	{
		free(((*ants)[index]).nbr);
		((*ants)[index]).nbr = NULL;
		index++;
	}
	free(*ants);
	*ants = NULL;
}

t_bool mangage_ants(t_result *result, t_info *info)
{
	t_ants *ants;

	ants = (t_ants *)malloc(sizeof(t_ants) * info->total_ants);
	if (ants == NULL)
		return (FALSE);
	if (assign_ants_order(result, ants, info->total_ants) == FALSE)
	{
		free_ants(&(ants), info->total_ants);
		return (FALSE);
	}
	print_ants(result, ants, info);
	free_ants(&(ants), info->total_ants);
	return (TRUE);
}
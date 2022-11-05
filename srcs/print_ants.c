/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:51:25 by thule             #+#    #+#             */
/*   Updated: 2022/11/05 14:54:00 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_ant_to_room(char *ant, char *room_name)
{
	write(1, "L", 1);
	ft_putstr(ant);
	write(1, "-", 1);
	ft_putstr(room_name);
	write(1, " ", 1);
}

void	print_ants_helper(t_ants *ants, t_info *info)
{
	int			ant_order;
	t_ants		curr_ant;
	t_path		*path;

	ant_order = 0;
	while (ant_order < info->total_ants)
	{
		curr_ant = ants[ant_order];
		path = curr_ant.path;
		if (curr_ant.position > path->len - 1)
		{
			info->end_room->is_occupied = FALSE;
			ant_order++;
			continue;
		}
		if (path->path[curr_ant.position]->is_occupied == FALSE
			|| path->path[curr_ant.position] == info->end_room)
		{
			print_ant_to_room(curr_ant.number, path->path[curr_ant.position]->room_name);
			path->path[curr_ant.position]->is_occupied = TRUE;
			if (curr_ant.position > 1)
				path->path[curr_ant.position - 1]->is_occupied = FALSE;
			ants[ant_order].position = ants[ant_order].position + 1;
		}
		ant_order++;
	}
}

void print_ants(t_result *result, t_ants *ants, t_info *info)
{
	int	flow;
	int	index;

	flow = result->min_turn;
	index = 0;
	while (index < flow)
	{
		print_ants_helper(ants, info);
		ft_putchar('\n');
		index++;
	}
}

void assign_ants_order(t_result *result, t_info *info, t_ants *ants)
{
	t_path	*path;
	int		path_order;
	int		index;

	path = result->best_paths;
	path_order = 0;
	index = -1;
	while (++index < info->total_ants)
	{
		if (path_order == result->total)
		{
			path = result->best_paths;
			path_order = 0;
		}
		if (result->divide_ants[path_order][1] > 0)
		{
			ants[index].number = ft_itoa(index + 1);
			if (ants[index].number == NULL)
			{
				//false protect,
				return ;
			}
			ants[index].path = path;
			ants[index].position = 1;
			(result->divide_ants[path_order][1])--;
		}
		else
			index--;
		path = path->next;
		path_order++;
	}
}

t_bool mangage_ants(t_result *result, t_info *info)
{
	t_ants	*ants;

	ants = (t_ants *)malloc(sizeof(t_ants) * info->total_ants);
	if (ants == NULL)
		return (FALSE);
	assign_ants_order(result, info, ants);
	print_ants(result, ants, info);
	free(ants);
	return (TRUE);
}
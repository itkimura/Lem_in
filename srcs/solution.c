/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/07 17:01:29 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* update one_two and two_one in link*/
void	update_link_weight(t_room *from, t_room *to, t_link *link, t_bool *flag)
{
	while (link)
	{
		if (link->room1 == from && link->room2 == to)
		{
			link->one_two = DROP;
			if (link->two_one != DROP)
				link->two_one = INVERSE;
			if (link->one_two == DROP && link->two_one == DROP)
				*flag = TRUE;
		}
		if (link->room2 == from && link->room1 == to)
		{
			link->two_one = DROP;
			if (link->one_two != DROP)
				link->one_two = INVERSE;
			if (link->two_one == DROP && link->one_two == DROP)
				*flag = TRUE;
		}
		link = link->next;
	}
}

/* update edge weight by paths */
t_bool	update_edge_weight(t_info *info, t_path *head)
{
	t_room	*from;
	t_room	*to;
	t_bool	flag;

	flag = FALSE;
	for (int i = 0; i < head->len - 1; i++)
	{
		from = head->path[i];
		to = head->path[i + 1];
		update_link_weight(from, to, info->link_head, &flag);
	}
	return (flag);
}

void	init_links(t_link *link)
{
	while (link)
	{
		if (!(link->one_two == DROP && link->two_one == DROP))
		{
			link->one_two = UNUSED;
			link->two_one = UNUSED;
		}
		link = link->next;
	}
}

void	init_path_nb(t_room *room)
{
	while (room)
	{
		room->path_nb = 0;
		room = room->list_next;
	}
}

/* if curr_turn becomes bigger than min_turn, then we found the shortest path set so return TRUE*/
t_bool	get_result_condition(t_info *info, t_result *result,\
							t_path *path_curr, int *count)
{
	static int keep;

	if (*count == 1)
		result->tmp_head = path_curr;
	init_path_nb(info->room_head);
	if (update_edge_weight(info, path_curr))
	{
		printf("--- remove edge ---\n");
		init_links(info->link_head);
		*count = 0;
	}
	else
	{
		count_turn(info, result, *count);
		if (*count == 1)
			keep = result->curr_turn;
		else
		{
			if (keep < result->curr_turn)
				return TRUE;
			keep = result->curr_turn;
		}
	}
	return (FALSE);
}

void	free_matrix(t_info *info)
{
	int	index;

	index = 0;
	if (info->matrix)
	{
		while (index < info->total_rooms)
		{
			if (info->matrix[index])
				free(info->matrix[index]);
			index++;
		}
		free(info->matrix);
		info->matrix = NULL;
	}
}

t_bool	get_result(t_info *info, t_result *result)
{
	t_path		*path_curr;
	t_path		*path_next;
	int			count;

	count = 1;
	path_curr = bfs(info);
	result->path_head = path_curr;
	result->curr_turn = 0;
	result->tmp_head = path_curr;
	count_turn(info, result, count);
	while (path_curr)
	{
		print_single_path(path_curr);
		if (get_result_condition(info, result, path_curr, &count))
			break ;
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
	}
	printf("--- res ---\n");
	printf("min = %d total = %d\n", result->min_turn, result->total);
	t_path *path = result->best_paths;
	for (int i = 0; i < result->total; i++)
	{
		print_single_path(path);
		path = path->next;
	}
	return (TRUE);
}

void	init_result(t_result *result)
{
	result->path_head = NULL;
	result->tmp_head = NULL;
	result->best_paths = NULL;
	result->min_turn = 0;
	result->curr_turn = 0;
	result->total = 0;
	result->divide_ants = NULL;
}
t_bool solution(t_info *info)
{
	t_result	result;

	init_result(&result);
	//printf("\n");
	get_result(info, &result);
	//if (result.best_paths == NULL)
	//	error("No path\n");
	//else
//		mangage_ants(&result, info);
	free_paths(result.path_head);
	free_divide_ants_array(&result.divide_ants, result.total);
	return (TRUE);
}

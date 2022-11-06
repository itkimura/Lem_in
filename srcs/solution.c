/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/06 12:57:02 by itkimura         ###   ########.fr       */
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
			link->one_two = 1;
			if (link->two_one != 1)
				link->two_one = -1;
			if (link->one_two == 1 && link->two_one == 1)
				*flag = TRUE;
		}
		if (link->room2 == from && link->room1 == to)
		{
			link->two_one = 1;
			if (link->one_two != 1)
				link->one_two = -1;
			if (link->two_one == 1 && link->one_two == 1)
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
	while (head)
	{
		for (int i = 0; i < head->len - 1; i++)
		{
			from = head->path[i];
			to = head->path[i + 1];
			update_link_weight(from, to, info->link_head, &flag);
		}
		head = head->next;
	}
	return (flag);
}

void	init_links(t_link *link)
{
	while (link)
	{
		if (!(link->one_two == 1 && link->two_one == 1))
		{
			link->one_two = 0;
			link->two_one = 0;
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
		//	return (TRUE);
		//if (result->curr_turn > result->min_turn && info->start_room->malloc_link >= result->total)
		//if (result->curr_turn > result->min_turn && info->start_room->malloc_link == result->total)
	printf("count  = %d curr_turn = %d min_turn = %d start = %d end = %d total = %d\n", *count, result->curr_turn, result->min_turn, info->start_room->malloc_link, info->end_room->malloc_link, result->total);
		//if (result->curr_turn >= result->min_turn && result->tmp_head == result->best_paths)
	//result->curr_turn > result->min_turn in the same bfs session -> return TRUE
	}
	//if (result->curr_turn > result->min_turn || info->start_room->malloc_link == result->total)
	//	return (TRUE);
	return (FALSE);
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
		//print_single_path(path_curr);
		if (get_result_condition(info, result, path_curr, &count))
			break ;
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
	}
	printf("min = %d total = %d\n", result->min_turn, result->total);
	t_path *path = result->best_paths;
	for (int i = 0; i < result->total; i++)
	{
		print_single_path(path);
		path = path->next;
	}
	return (TRUE);
}

t_bool solution(t_info *info)
{
	t_result	result;
	
	ft_memset(&result, 0, sizeof(result));
	print_info(info);
	printf("\n");
	get_result(info, &result);
	if (result.best_paths == NULL)
		error("No path\n");
	else
		mangage_ants(&result, info);
	free_paths(result.path_head);
	free_divide_ants_array(&result.divide_ants, result.total);
	return (TRUE);
}

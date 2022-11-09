/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/09 15:23:26 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* 
 * if curr_turn becomes bigger than min_turn,
 * then we found the shortest path set so return TRUE
 */
t_bool	get_result_condition(t_info *info, t_result *result,
							t_path *path_curr, int *count)
{
	static int	keep;

	if (*count == 1)
		result->tmp_head = path_curr;
	if (update_link_weight(info, path_curr))
	{
		init_unused_links(info, result->tmp_head);
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
				return (TRUE);
			keep = result->curr_turn;
		}
	}
	return (FALSE);
}

t_bool	get_result(t_info *info, t_result *result)
{
	t_path	*path_curr;
	t_path	*path_next;
	int		count;

	count = 1;
	path_curr = NULL;
	if (bfs(info, &path_curr, TRUE) == FALSE || path_curr == NULL)
		return (FALSE);
	result->path_head = path_curr;
	result->curr_turn = 0;
	result->tmp_head = path_curr;
	count_turn(info, result, count);
	while (path_curr)
	{
		if (get_result_condition(info, result, path_curr, &count))
			break ;
		path_next = NULL;
		if (bfs(info, &path_next, TRUE) == FALSE)
			return (FALSE);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
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

t_bool	solution(t_info *info)
{
	t_result	result;
	t_bool		flag;

	flag = TRUE;
	init_result(&result);
	if (get_result(info, &result) == FALSE)
		flag = FALSE;
	else
		mangage_ants(&result, info);
	free_paths(result.path_head);
	free_divide_ants_array(&result.divide_ants, result.total);
	return (flag);
}

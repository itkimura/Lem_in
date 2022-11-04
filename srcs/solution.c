/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/04 17:31:32 by thule            ###   ########.fr       */
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

void	get_result_condition(t_info *info, t_result *result,\
							t_path *path_curr, int *count)
{
	if (*count == 1)
		result->tmp_head = path_curr;
	init_path_nb(info->room_head);
	if (update_edge_weight(info, path_curr))
	{
		init_links(info->link_head);
		*count = 0;
	}
	else
		count_turn(info, result, *count);
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
		get_result_condition(info, result, path_curr, &count);
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
	}
	return (TRUE);
}

t_bool solution(t_info *info)
{
	t_result	result;
	
	ft_memset(&result, 0, sizeof(result));
	get_result(info, &result);

	t_path *tmp;
	int		index;

	index = 0;
	tmp = result.best_paths;
	printf("total: %d | min: %d\n", result.total, result.min_turn);
	while (index < result.total && tmp)
	{
		print_single_path(tmp);
		tmp = tmp->next;
		index++;
	}
	for (int i = 0; i < result.total ; i++)
        printf("[%d] path[0] = %d path[1] = %d total:%d\n", i+1, result.divide_ants[i][0], result.divide_ants[i][1], result.divide_ants[i][0] + result.divide_ants[i][1] - 1);
	free_paths(result.path_head);
	free_divide_ants_array(&result.divide_ants, result.total);
	return (TRUE);
}

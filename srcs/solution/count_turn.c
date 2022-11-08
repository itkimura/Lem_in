/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 13:24:31 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
 * path[0] = length of each path
 * path[1] = how many ants
 */

static t_bool	init_path_array(t_path *list, int count_path, int ***path)
{
	t_path	*tmp;
	int		i;

	*path = (int **)malloc(sizeof(int *) * count_path);
	if (path == NULL)
		return (FALSE);
	i = 0;
	tmp = list;
	while (i < count_path)
	{
		(*path)[i] = (int *)malloc(sizeof(int) * 2);
		if ((*path)[i] == NULL)
		{
			while (--i)
				free(path[i]);
			free(path);
			return (FALSE);
		}
		(*path)[i][PATH_LEN] = tmp->len - 1;
		(*path)[i][ANTS] = 0;
		tmp = tmp->next;
		i++;
	}
	return (TRUE);
}

/*
 * path[0] = length of each path
 * path[1] = how many ants
 */

/* devide ants in paths */
static void		divide_ants(t_info *info, int **path, int count_path)
{
	int	i; /* loop for ants one by one*/
	int	j; /* loop for path one by one*/
	int	next;
	int	prev; /* tmp int for compering paths*/

	i = 1;
	path[0][ANTS]++;
	while (i < info->total_ants)
	{
		j = 0;
		while (j < count_path - 1)
		{
			prev = path[j][PATH_LEN] + path[j][ANTS];
			next = path[j + 1][PATH_LEN] + path[j + 1][ANTS];
			if (prev < next)
				break;
			j++;
		}
		path[j][ANTS]++;
		i++;
	}
}

t_bool		count_turn(t_info *info, t_result *result, int count_path)
{
	int	**path;
	int	i;

	i = 0;
	if (init_path_array(result->tmp_head, count_path, &path) == FALSE)
		return (FALSE);
	result->curr_turn = 0;
	divide_ants(info, path, count_path);
	while (i < count_path)
	{
		if (result->curr_turn < path[i][PATH_LEN] - 1 + path[i][ANTS])
			result->curr_turn = path[i][PATH_LEN] - 1 + path[i][ANTS];
		i++;
	}
	if (result->min_turn > result->curr_turn || result->min_turn == 0)
	{
		free_divide_ants_array(&(result->divide_ants), result->total);
		result->min_turn = result->curr_turn;
		result->total = count_path;
		result->best_paths = result->tmp_head;
		result->divide_ants = path;
	}
	else
		free_divide_ants_array(&path, count_path);
	return (TRUE);
}

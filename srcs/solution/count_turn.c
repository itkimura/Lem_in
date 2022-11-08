/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 20:23:53 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
 * devide ants in paths
 * i -> loop for ants one by one
 * j -> loop for path one by one
 * prec -> tmp int for compering paths
 */
static void	divide_ants(t_info *info, int **path, int count_path, int *curr_turn)
{
	int	i;
	int	j;
	int	next;
	int	prev;

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
				break ;
			j++;
		}
		path[j][ANTS]++;
		if (path[j][PATH_LEN] - 1 + path[j][ANTS] > *curr_turn)
			*curr_turn = path[j][PATH_LEN] - 1 + path[j][ANTS];
		i++;
	}
}

t_bool	count_turn(t_info *info, t_result *result, int count_path)
{
	int	**path;

	if (init_path_array(result->tmp_head, count_path, &path) == FALSE)
		return (FALSE);
	result->curr_turn = 0;
	divide_ants(info, path, count_path, &(result->curr_turn));
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

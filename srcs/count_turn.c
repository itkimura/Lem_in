/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/05 21:22:38 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*
 * path[0] = length of each path
 * path[1] = how many ants
 */

t_bool		init_path_array(t_path *list, int count_path, int ***path)
{
	t_path	*tmp;
	int		index;

	*path = (int **)malloc(sizeof(int *) * count_path);
	if (path == NULL)
		return (FALSE);
	index = 0;
	tmp = list;
	while (index < count_path)
	{
		(*path)[index] = (int *)malloc(sizeof(int) * 2);
		if ((*path)[index] == NULL)
		{
			while (--index)
				free(path[index]);
			free(path);
			return (FALSE);
		}
		(*path)[index][0] = tmp->len - 1;
		(*path)[index][1] = 0;
		tmp = tmp->next;
		index++;
	}
	return (TRUE);
}

/*
 * path[0] = length of each path
 * path[1] = how many ants
 */

/* devide ants in paths */
void		divide_ants(t_info *info, int **path, int count_path)
{
	int	i; /* loop for ants one by one*/
	int	j; /* loop for path one by one*/
	int	next;
	int	prev; /* tmp int for compering paths*/

	i = 0;
	while (i < info->total_ants)
	{
		if (i == 0)
			path[0][1]++;
		else
		{
			j = 0;
			while (j < count_path - 1)
			{
				prev = path[j][0] + path[j][1];
				next = path[j + 1][0] + path[j + 1][1];
				if (prev < next)
				{
					path[j][1]++;
					break;
				}
				j++;
			}
			if (j == count_path - 1)
				path[j][1]++;
		}
		i++;
	}
}

void	free_divide_ants_array(int ***path, int count_path)
{
	int	index;
	
	index = 0;
	while (index < count_path)
	{
		free((*path)[index]);
		index++;
	}
	free(*path);
}

t_bool		count_turn(t_info *info, t_result *result, int count_path)
{
	int	**path;
	int	index;

	index = 0;
	if (init_path_array(result->tmp_head, count_path, &path) == FALSE)
		return (FALSE);
	divide_ants(info, path, count_path);
	result->curr_turn = 0;
	while (index < count_path)
	{
		if (result->curr_turn < path[index][0] - 1 + path[index][1])
			result->curr_turn = path[index][0] - 1 + path[index][1];
		index++;
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

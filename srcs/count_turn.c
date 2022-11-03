/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/03 13:27:26 by itkimura         ###   ########.fr       */
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
void		devide_ants(t_info *info, int ***path, int count_path)
{
	int	i; /* loop for ants one by one*/
	int	j; /* loop for path one by one*/
	int	next;
	int	prev; /* tmp int for compering paths*/

	i = 0;
	while (i < info->total_ants)
	{
		if (i == 0)
			(*path)[0][1]++;
		else
		{
			j = 0;
			while (j < count_path - 1)
			{
				prev = (*path)[j][0] + (*path)[j][1];
				next = (*path)[j + 1][0] + (*path)[j + 1][1];
				if (prev < next)
				{
					(*path)[j][1]++;
					break;
				}
				j++;
			}
			if (j == count_path - 1)
				(*path)[j][1]++;
		}
		i++;
	}
}

t_bool		count_turn(t_info *info, t_path *list, int count_path, int *curr_turn)
{
	int	**path;

	if (init_path_array(list, count_path, &path) == FALSE)
		return (FALSE);
	devide_ants(info, &path, count_path);
	*curr_turn = 0;
	for (int i = 0; i < count_path ; i++)
	{
		if (*curr_turn < path[i][0] - 1 + path[i][1])
			*curr_turn = path[i][0] - 1 + path[i][1];
	}
	//for (int i = 0; i < count_path ; i++)
	//	printf("path[0] = %d path[1] = %d total:%d\n", path[i][0], path[i][1], path[i][0] + path[i][1]);
	return (TRUE);
}

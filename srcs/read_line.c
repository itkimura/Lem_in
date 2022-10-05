/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/10/05 10:37:18 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int type_of_line(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	else if (str[0] == '#' && str[1] != '#')
		return (COMMENT);
	else if (str[0] == '#')
		return (COMMAND);
	else if (ft_strchr(str, '-') && ft_strchr(str, ' ') == NULL)
		return (LINK);
	return (ROOM);
}

e_bool get_ants(t_info *info, int type, int *stage)
{
	long nb;
	int i;

	i = 0;
	if (type == COMMENT)
		return (TRUE);
	if (type != ROOM)
		return (FALSE);
	while (info->line[i])
	{
		if (!(info->line[i] >= '0' && info->line[i] <= '9'))
			return (error("Wrong format for ants.\n"), FALSE);
		i++;
	}
	nb = ft_atol(info->line);
	if (nb < 0 || nb > INT_MAX)
		return (error("Quantity of ants is not correct."), FALSE);
	info->quantity_of_ants = nb;
	(*stage)++;
	return (TRUE);
}

e_bool path_to_each_stage(t_info *info, int type, int *stage)
{
	if (*stage == 0)
	{
		if (get_ants(info, type, stage) == FALSE)
			return (FALSE);
	}
	else if (*stage == 1)
	{
		if (type == LINK)
			(*stage)++;
		else if (get_rooms(info, type) == FALSE)
			return (FALSE);
	}
	if (*stage == 2)
	{
		if (type == ROOM)
			return FALSE;
	}
	return (TRUE);
}

e_bool read_line(t_info *info)
{
	int type;
	int stage;
	int gnl;

	gnl = 1;
	stage = 0;
	while (gnl)
	{
		gnl = get_next_line(FD, &(info->line));
		if (gnl < 0)
			return (error("GNL return -1\n"), exit(1), FALSE);
		type = type_of_line(info->line);
		if (type != COMMENT)
		{
			if (path_to_each_stage(info, type, &stage) == FALSE)
				return (FALSE);
		}
		if (gnl != 0)
			free(info->line);
	}
	init_hash_table(info);
	return (TRUE);
}

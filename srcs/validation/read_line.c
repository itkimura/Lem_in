/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/09 14:35:11 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	type_of_line(char *str)
{
	if (str[0] == '\0')
		return (EMPTY);
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

t_bool	get_ants(t_info *info, int type, int *stage)
{
	long	nb;
	int		i;

	i = 0;
	if (type != ROOM)
		return (FALSE);
	while (info->line[i])
	{
		if (!(info->line[i] >= '0' && info->line[i] <= '9'))
			return (FALSE);
		i++;
	}
	nb = ft_atol(info->line);
	if (nb < 0 || nb > INT_MAX)
		return (FALSE);
	info->total_ants = nb;
	(*stage)++;
	return (TRUE);
}

t_bool	path_to_each_stage(t_info *info, int type, int *stage)
{
	if (*stage == 0)
	{
		if (get_ants(info, type, stage) == FALSE)
			return (FALSE);
	}
	else if (*stage == 1)
	{
		if (type == LINK && (*stage)++)
		{
			if ((info->start_room == NULL || info->end_room == NULL)
				|| init_room_hash_table(info) == FALSE)
				return (FALSE);
			return (get_links(info));
		}
		else if (get_rooms(info, type) == FALSE)
			return (FALSE);
	}
	if (*stage == 2)
	{
		if (type == ROOM)
			return (FALSE);
		if (type != COMMAND)
			return (get_links(info));
	}
	return (TRUE);
}

t_bool	read_line(t_info *info, t_bool flag)
{
	int	type;
	int	stage;
	int	gnl;

	gnl = 1;
	stage = 0;
	while (gnl)
	{
		gnl = get_next_line(FD, &(info->line));
		if (gnl == 0)
			break ;
		if (gnl < 0)
			return (FALSE);
		ft_putstr_fd(info->line, 1);
		write(1, "\n", 1);
		type = type_of_line(info->line);
		if (type == EMPTY
			|| (stage == 0 && (type == COMMENT || type == COMMAND)))
			flag = FALSE;
		if (type != COMMENT && flag == TRUE)
			flag = path_to_each_stage(info, type, &stage);
		free(info->line);
	}
	return (flag);
}

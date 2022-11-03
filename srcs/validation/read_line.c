/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/03 11:45:46 by itkimura         ###   ########.fr       */
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
	if (type == COMMAND)
		return (TRUE);
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
			if (info->start_room == NULL || info->end_room == NULL)
				return (FALSE);
			return (init_hash_table(info), get_links(info));
		}
		else if (get_rooms(info, type) == FALSE)
			return (FALSE);
	}
	if (*stage == 2)
	{
		if (type == ROOM)
			return (FALSE);
		if (type == COMMAND)
			return (TRUE);
		return (get_links(info));
	}
	return (TRUE);
}

t_bool	read_line(t_info *info)
{
	int		type;
	int		stage;
	int		gnl;
	t_bool	flag;

	gnl = 1;
	stage = 0;
	flag = TRUE;
	while (gnl)
	{
		gnl = get_next_line(FD, &(info->line));
		if (gnl == 0)
			break ;
		if (gnl < 0)
			return (error("GNL return -1\n"), FALSE);
		//ft_putstr(info->line);
		//ft_putchar('\n');
		type = type_of_line(info->line);
		if (type == EMPTY)
			flag = FALSE;
		if (type != COMMENT && flag == TRUE)
			flag = path_to_each_stage(info, type, &stage);
		free(info->line);
	}
	return (flag);
}

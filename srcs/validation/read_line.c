/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/09 13:18:12 by thle             ###   ########.fr       */
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
			return (print_error("Wrong format for ants.\n"), FALSE);
		i++;
	}
	nb = ft_atol(info->line);
	if (nb < 0 || nb > INT_MAX)
		return (print_error("Quantity of ants is not correct."), FALSE);
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
			return (print_error("GNL return -1\n"), FALSE);
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

// t_bool assign_line(t_info *info, t_bool flag)
// {
// 	int	type;
// 	int	stage;
// 	char *end;

// 	stage = 0;
// 	info->line = info->big_line;
// 	end = info->big_line;
// 	while (1)
// 	{
// 		end = ft_strchr(info->line, '\n');
// 		if (end == NULL)
// 			break ;
// 		*end = '\0';
// 		ft_putstr_fd(info->line, 1);
// 		write(1, "\n", 1);
// 		type = type_of_line(info->line);
// 		if (type == EMPTY
// 			|| (stage == 0 && (type == COMMENT || type == COMMAND)))
// 			flag = FALSE;
// 		if (type != COMMENT && flag == TRUE)
// 			flag = path_to_each_stage(info, type, &stage);
// 		info->line = end + 1;
// 	}
// 	return flag;
// }

// t_bool	read_line(t_info *info, t_bool flag)
// {
// 	int		ret;
// 	char	buff[BUFF_SIZE + 1];
// 	char	*line;

// 	ret = 1;
// 	if (info->line == NULL)
// 	{
// 		info->big_line = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
// 		if (info->big_line == NULL)
// 			return (FALSE);
// 	}
// 	ret = read(FD, info->big_line, BUFF_SIZE);
// 	if (ret <= 0)
// 	{
// 		free(info->big_line);
// 		return FALSE;
// 	}
// 	if (ret <= BUFF_SIZE)
// 	{
// 		info->big_line[ret] = '\0';
// 		// flag = assign_line(info, flag);
// 	}
// 	while (ret > 0)
// 	{
// 		ret = read(FD, buff, BUFF_SIZE);
// 		if (ret < 0)
// 		{
// 			free(info->big_line);
// 			flag = FALSE;
// 			break ;
// 		}
// 		if (ret == 0)
// 			break ;
// 		buff[ret] = '\0';
// 		line = ft_strjoin(info->big_line, buff);
// 		free(info->big_line);
// 		info->big_line = line;
// 	}
// 	if (flag == TRUE)
// 		flag = assign_line(info, flag);
// 	return (flag);
// }
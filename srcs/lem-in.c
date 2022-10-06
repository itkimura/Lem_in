/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/10/06 15:18:36 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool init_info(t_info *info)
{
	info->quantity_of_ants = 0;
	info->quantity_of_rooms = 0;
	info->start_room = NULL;
	info->end_room = NULL;
	info->room_head = NULL;
	info->line = NULL;
	info->room_head = NULL;
	info->hash_table = NULL;
	return (TRUE);
}

t_bool check_digit_and_space(char *line)
{
	int i;
	int space;

	i = 1;
	space = 0;
	if (line == NULL || line[0] != ' ')
		return (FALSE);
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			space++;
		if ((ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '+') || space > 1)
			return (FALSE);
		if (line[i] == ' ' && (ft_isdigit(line[i + 1]) == 0 || line[i + 1] == '+'))
			return (FALSE);
		i++;
	}
	if (space == 0)
		return (FALSE);
	return (TRUE);
}

t_bool check_xy(char *line)
{
	long x;
	long y;

	if (check_digit_and_space(line) == FALSE)
		return (FALSE);
	x = ft_atol(line);
	y = ft_atol(ft_strchr(line + 1, ' '));
	if ((x > INT_MAX || x < INT_MIN) || (y > INT_MAX || y < INT_MIN))
		return (FALSE);
	return (TRUE);
}

t_bool lem_in(void)
{
	t_info info;

	if (init_info(&info) == FALSE)
		return (FALSE);
	if (read_line(&info) == FALSE)
	{
		free_rooms(&(info.room_head));
		return (FALSE);
	}
	/*Delete start here*/
	// print_info(&info);
	// print_room(info.room_head);
	/*Delete end here*/
	free_rooms(&(info.room_head));
	return (TRUE);
}

int main(void)
{
	if (lem_in() == FALSE)
		return (1);
	return (0);
}

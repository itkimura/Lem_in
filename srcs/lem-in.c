/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 21:08:23 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	error(char *error)
{
	ft_putstr_fd(error, 2);
}

/* Itoe */
e_bool	init_info(t_info *info)
{
	// info = (t_info *)malloc(sizeof(t_info));
	info->quantity_of_ants = 0;
	info->quantity_of_rooms = 0;
	info->start_room = NULL;
	info->end_room = NULL;
	info->head = NULL;
	return (TRUE);
}

e_bool	check_digit_and_space(char *line)
{
	int i;
	int space;

	i = 1;
	space = 0;
	if (line == NULL || line[0] != ' ')
		return FALSE;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			space++;
		if ((ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '+')
			|| space > 1)
			return FALSE;
		if (line[i] == ' ' && (ft_isdigit(line[i + 1]) == 0 || line[i + 1] == '+'))
			return FALSE;
		i++;
	}
	if (space == 0)
		return FALSE;
	return TRUE;
}

/* itoe */
e_bool	check_xy(char *line)
{
	long x;
	long y;

	if (check_digit_and_space(line) == FALSE)
		return FALSE;
	x = ft_atol(line);
	y = ft_atol(ft_strchr(line + 1, ' '));
	if ((x > INT_MAX || x < INT_MIN) || (y > INT_MAX || y < INT_MIN))
		return (FALSE);
	return (TRUE);
}

void print_info(t_info *info)
{
	printf("quantity_of_ants: %d\n", info->quantity_of_ants);
	printf("quantity_of_rooms: %d\n", info->quantity_of_rooms);
	printf("start_room: %s\n", info->start_room);
	printf("end_room: %s\n", info->end_room);
}

e_bool	lem_in()
{
	t_info info;
	t_room *head;

	// info = NULL;
	head = NULL;
	if (init_info(&info) == FALSE)
	{
		return (FALSE);
	}
	// print_info(info);
	if (read_line(head, &info) == FALSE)
	{
		// free_rooms(&head);
		return (FALSE);
	}
	print_info(&info);
	print_room(info.head);
	return TRUE;
}

int main(void)
{
	// printf("hello\n");
	if (lem_in() == FALSE)
		return (1);
	return (0);
}

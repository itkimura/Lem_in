/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 16:55:03 by itkimura         ###   ########.fr       */
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
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (FALSE);
	info->quantity_of_ants = 0;
	info->quantity_of_rooms = 0;
	info->start_room = -1;
	info->end_room = -1;
	return (TRUE);
}

/* itoe */
e_bool	get_xy(char *line, t_room *tmp)
{
	long nb;
	tmp->x = ;
	tmp->y = ;
	/*if not space or non numeric letter*/
	return (FALSE);
	/* no error */
	return (TRUE);
}

e_bool	lem_in()
{
	t_info *info;
	t_room *head;

	info = NULL;
	head = NULL;
	if (init_info(&info) == FALSE)
		return (FALSE);
	if (read_line(&room) == FALSE)
	{
		free_rooms(&head);
		return (FALSE);
	}
}

int main(void)
{
	printf("hello\n");
	if (lem-in(void) == FALSE)
		return (1);
	return (0);
}

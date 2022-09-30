/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 14:53:50 by itkimura         ###   ########.fr       */
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
	malloc fail ->
		return (FALSE);
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

void	lem_in()
{
	t_info *info;
	t_room *head;

	info = NULL;
	head = NULL;
	if (!read_line(&room))
	{
		free_rooms(&head);
		return (0);
	}
	init_info(&info);
}

int main(void)
{
	printf("hello\n");
	if (!lem-in())
		return (1);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/11/09 14:37:38 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_error(char *print_error)
{
	ft_putstr_fd(print_error, 1);
}

void	print_ant(char *ant, char *room_name)
{
	write(1, "L", 1);
	ft_putstr_fd(ant, 1);
	write(1, "-", 1);
	ft_putstr_fd(room_name, 1);
	write(1, " ", 1);
}

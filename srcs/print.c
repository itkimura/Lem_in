/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 17:03:17 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_error(char *print_error)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(print_error, 2);
	ft_putstr_fd("\033[0;37m", 2);
}

void	print_ant(char *ant, char *room_name)
{
	write(1, "L", 1);
	ft_putstr(ant);
	write(1, "-", 1);
	ft_putstr(room_name);
	write(1, " ", 1);
}

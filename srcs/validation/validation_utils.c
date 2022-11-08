/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:51:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 11:51:51 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	check_digit_and_space(char *line)
{
	int	i;
	int	space;

	i = 1;
	space = 0;
	if (line == NULL || line[0] != ' ')
		return (FALSE);
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			space++;
		if ((ft_isdigit(line[i]) == 0 && line[i] != ' '
				&& line[i] != '+') || space > 1)
			return (FALSE);
		if (line[i] == ' ' && (ft_isdigit(line[i + 1]) == 0
				|| line[i + 1] == '+'))
			return (FALSE);
		i++;
	}
	if (space == 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_xy(char *line)
{
	long	x;
	long	y;

	if (check_digit_and_space(line) == FALSE)
		return (FALSE);
	x = ft_atol(line);
	y = ft_atol(ft_strchr(line + 1, ' '));
	if ((x > INT_MAX || x < INT_MIN) || (y > INT_MAX || y < INT_MIN))
		return (FALSE);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/10/07 14:44:01 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error(char *error)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0;37m", 2);
}

void	free_rooms(t_room **head)
{
	t_room	*next;
	t_room	*current;

	current = *head;
	while (current)
	{
		next = current->list_next;
		free(current->room_name);
		free(current->link);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_links(t_link **link)
{
	t_link	*next;
	t_link	*current;

	current = *link;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*link = NULL;
}

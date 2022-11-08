/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:27:06 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 15:48:13 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void free_rooms(t_room **head)
{
	t_room *next;
	t_room *current;

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

void free_links(t_link **link)
{
	t_link *next;
	t_link *current;

	current = *link;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*link = NULL;
}

void free_divide_ants_array(int ***path, int count_path)
{
	int i;

	i = 0;
	if (path && *path)
	{
		while (i < count_path)
		{
			if ((*path)[i])
				free((*path)[i]);
			i++;
		}
		free(*path);
	}
}

void free_ants(t_ants **ants, int total_ants)
{
	int index;

	index = 0;
	if (ants)
	{
		while (index < total_ants)
		{
			if ((*ants)[index].nbr)
			{
				free(((*ants)[index]).nbr);
				((*ants)[index]).nbr = NULL;
			}
			index++;
		}
		free(*ants);
		*ants = NULL;
	}
}

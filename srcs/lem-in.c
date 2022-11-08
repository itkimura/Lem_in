/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 13:43:36 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool init_info(t_info *info)
{
	info->total_ants = 0;
	info->total_rooms = 0;
	info->total_links = 0;
	info->start_room = NULL;
	info->end_room = NULL;
	info->room_head = NULL;
	info->line = NULL;
	info->room_head = NULL;
	info->hash_table = NULL;
	info->link_hash_table = NULL;
	info->link_head = NULL;
	return (TRUE);
}

t_bool lem_in(void)
{
	t_info info;

	if (init_info(&info) == FALSE)
		return (print_error("\nprint_error.\n"), FALSE);
	if (read_line(&info) == FALSE)
	{
		free_rooms(&(info.room_head));
		if (info.hash_table)
			free(info.hash_table);
		return (print_error("\nprint_error.\n"), FALSE);
	}
	if (connect_rooms(&info) == FALSE)
	{
		free_rooms(&(info.room_head));
		free_links(&(info.link_head));
		if (info.hash_table)
			free(info.hash_table);
		return (print_error("\nprint_error.\n"), FALSE);
	}
	if (init_link_hash_table(&info) == FALSE)
	{
		free(info.hash_table);
		free_rooms(&(info.room_head));
		free_links(&(info.link_head));
		return (FALSE);
	}
	solution(&info);
	free(info.hash_table);
	free(info.link_hash_table);
	free_rooms(&(info.room_head));
	free_links(&(info.link_head));
	return (TRUE);
}

int main(void)
{
	if (lem_in() == FALSE)
		return (1);
	return (0);
}

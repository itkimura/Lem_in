/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 18:08:37 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool	init_info(t_info *info)
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

void	free_all(t_info *info)
{
	if (info->hash_table)
		free(info->hash_table);
	if (info->link_hash_table)
		free(info->link_hash_table);
	free_rooms(&(info->room_head));
	free_links(&(info->link_head));
}

t_bool	lem_in(void)
{
	t_info	info;
	t_bool	flag;

	flag = init_info(&info);
	if (flag == TRUE)
		flag = read_line(&info, TRUE);
	if (flag == TRUE)
		flag = connect_rooms(&info);
	if (flag == TRUE)
		flag = init_link_hash_table(&info);
	if (flag == TRUE)
		solution(&info);
	free_all(&info);
	if (flag == FALSE)
		return (print_error("\nError\n"), FALSE);
	return (TRUE);
}

int	main(void)
{
	if (lem_in() == FALSE)
		return (1);
	return (0);
}

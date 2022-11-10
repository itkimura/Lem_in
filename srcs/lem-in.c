/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/10 17:42:23 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_bool	init_info(t_info *info)
{
	info->start_room = NULL;
	info->end_room = NULL;
	info->room_head = NULL;
	info->link_head = NULL;
	info->line = NULL;
	info->total_ants = 0;
	info->total_rooms = 0;
	info->total_links = 0;
	info->hash_table = NULL;
	info->link_hash_table = NULL;
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
		flag = solution(&info);
	free_all(&info);
	if (flag == FALSE)
		print_error("\nError\n");
	return (flag);
}

int	main(void)
{
	if (lem_in() == FALSE)
		return (1);
	return (0);
}

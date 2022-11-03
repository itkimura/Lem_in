/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/03 22:53:44 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* update edge weight by paths */
void	update_edge_weight(t_info *info, t_path *head)
{
	while (head)
	{
		for (int i = 0; i < head->len - 1; i++)
		{
			t_room *from = head->path[i];
			t_room *to = head->path[i + 1];
			t_link *link_tmp = info->link_head;
			while (link_tmp)
			{
				if (link_tmp->room1 == from && link_tmp->room2 == to)
				{
					link_tmp->one_two = 1;
					link_tmp->two_one = -1;
				}
				if (link_tmp->room2 == from && link_tmp->room1 == to)
				{
					link_tmp->two_one = 1;
					link_tmp->one_two = -1;
				}
				link_tmp = link_tmp->next;
			}
		}
		head = head->next;
	}
}

t_bool	get_paths(t_info *info)
{
	t_path *path_curr;
	t_path *path_next;

	path_curr = bfs(info);
	while (path_curr)
	{
		print_single_path(path_curr);
		update_edge_weight(info, path_curr);
		path_next = bfs(info);
		free_path(path_curr);
		path_curr = path_next;
	}
	return (TRUE);
}

t_bool solution(t_info *info)
{
	printf("_____START BFS____\n");
	get_paths(info);
	return (TRUE);
}

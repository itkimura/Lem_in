/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:10:45 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/02 15:49:02 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/*delete all links and initiarize mallok_link = 0 */
void	delete_link_from_room(t_info *info)
{
	t_room *room;

	room = info->room_head;
	while (room)
	{
		free(room->link);
		room->link = NULL;
		room->malloc_link = 0;
		room = room->list_next;
	}
}

void	init_links(t_info *info)
{
	t_link	*tmp;

	tmp = info->link_head;
	while (tmp)
	{
		tmp->one_two = NORMAL_WEIGHT;
		tmp->two_one = NORMAL_WEIGHT;
		tmp = tmp->next;
	}
}

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
					link_tmp->one_two = -1;
				if (link_tmp->room2 == from && link_tmp->room1 == to)
					link_tmp->two_one = -1;
				link_tmp = link_tmp->next;
			}
		}
		head = head->next;
	}
}


/* remove the inverse edge from the linked list of edges(links) */
t_bool	remove_inverse_edge(t_info *info)
{
	t_link	*curr;
	t_link	*tmp;
	t_link	*next;
	t_bool	flag;

	flag = FALSE;
	curr = info->link_head;
	while (curr)
	{
		tmp = curr->next;
		if (tmp == NULL)
			break ;
		next = tmp;
		while (tmp->one_two < 0 && tmp->two_one < 0)
		{
			flag = TRUE;
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		curr->next = next;
		curr = next;
	}
	return (flag);
}

void	update_links(t_info *info, t_path *head)
{
	(void)head;
	/*remove inverse links*/
	remove_inverse_edge(info);
	/*delete all links and initiarize mallok_link = 0 */
	//delete_link_from_room(info);
	/*re connect _rooms again*/
	//connect_rooms(info);
	/* init links*/
	//init_links(info);
}

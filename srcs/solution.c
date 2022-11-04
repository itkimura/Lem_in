/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/04 15:54:36 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* update one_two and two_one in link*/
void	update_link_weight(t_room *from, t_room *to, t_link *link, t_bool *flag)
{
	while (link)
	{
		if (link->room1 == from && link->room2 == to)
		{
			link->one_two = 1;
			if (link->two_one != 1)
				link->two_one = -1;
			if (link->one_two == 1 && link->two_one == 1)
				*flag = TRUE;
		}
		if (link->room2 == from && link->room1 == to)
		{
			link->two_one = 1;
			if (link->one_two != 1)
				link->one_two = -1;
			if (link->two_one == 1 && link->one_two == 1)
				*flag = TRUE;
		}
		link = link->next;
	}
}

/* update edge weight by paths */
t_bool	update_edge_weight(t_info *info, t_path *head)
{
	t_room	*from;
	t_room	*to;
	t_bool	flag;

	flag = FALSE;
	while (head)
	{
		for (int i = 0; i < head->len - 1; i++)
		{
			from = head->path[i];
			to = head->path[i + 1];
			update_link_weight(from, to, info->link_head, &flag);
		}
		head = head->next;
	}
	return (flag);
}

void	init_links(t_link *link)
{
	while (link)
	{
		if (!(link->one_two == 1 && link->two_one == 1))
		{
			link->one_two = 0;
			link->two_one = 0;
		}
		link = link->next;
	}
}

void	init_path_nb(t_room *room)
{
	while (room)
	{
		room->path_nb = 0;
		room = room->list_next;
	}
}

t_bool	get_paths(t_info *info)
{
	t_path *path_curr;
	t_path *path_next;
	t_path *path_head;

	t_path *tmp_head;
	t_path	*best_paths;
	int		total;
	int		min_turn;
	int		curr_turn;
	int		count;

	/* get the first path from bfs */
	count = 1;
	path_curr = bfs(info);
	path_head = path_curr;
	/* save min_turn with the shortest path*/
	curr_turn = 0;
	count_turn(info, path_head, count, &curr_turn);
	min_turn = curr_turn;
	total = count;
	//printf("min = %d total = %d\n", min_turn, total);
	//print_links(info);
	printf("_____START BFS____\n");
	while (path_curr)
	{
		//printf("count:%d ", count);
		if (count == 1)
			tmp_head = path_curr;
		//print_single_path(path_curr);
		//printf("--- bfs %d ---\n", count++);
		init_path_nb(info->room_head);
		if (update_edge_weight(info, path_curr))
		{
			init_links(info->link_head);
		//	printf("--- remove inverse edge ---\n");
			count = 0;
		}
		else
		{
			count_turn(info, tmp_head, count, &curr_turn);
			if (min_turn > curr_turn)
			{
				min_turn = curr_turn;
				total = count;
		//		printf("tmp_head: ");
		//		print_single_path(tmp_head);
				best_paths = tmp_head;
			}
			//printf("curr_turn = %d min = %d total = %d\n", curr_turn, min_turn, total);
		}
		//print_links(info);
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
	}
	//printf("--- all paths ---\n");
	//print_paths(path_head);
	//printf("--- best paths ---\n");
	//printf("curr_turn = %d min = %d total = %d\n", curr_turn, min_turn, total);
	/*
	if (best_paths == NULL)
		printf("best_paths empty\n");
	else
	{
		t_path *tmp = best_paths;
		for (int i = 0; i < total; i++)
		{
			if (tmp == NULL)
				break ;
			print_single_path(tmp);
			tmp = tmp->next;
		}
	}
	*/
	free_paths(path_head);
	return (TRUE);
}

void	test(t_info *info)
{
	t_path *path;

	path = bfs(info);
	print_single_path(path);

	print_rooms(info->room_head);
}

t_bool solution(t_info *info)
{
	printf("_____START BFS____\n");
	//test(info);
	get_paths(info);
	return (TRUE);
}

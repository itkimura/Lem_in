<<<<<<< HEAD

#include "../includes/lemin.h"

t_bool create_visited(t_info *info, t_bool **visited)
{
	*visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (visited == NULL)
		return (FALSE);
	ft_memset(*visited, FALSE, sizeof(t_bool) * info->total_rooms);
	return (TRUE);
}

t_bool check_visited(t_path *curr, t_bool *visited)
{
	int index;

	index = 1;
	print_single_path(curr);
	while (index < curr->len - 1)
	{
		if (visited[curr->path[index]->index] == TRUE)
			return (FALSE);
		else
			visited[curr->path[index]->index] = TRUE;
		index++;
	}
	return (TRUE);
}

t_bool update_min(t_info *info, t_path *list, int *min_turn, int *total_path)
{
	t_bool *visited;
	t_path *head;
	int count_path;
	int curr_turn;

	visited = NULL;
	if (create_visited(info, &visited) == FALSE)
		return (FALSE);
	count_path = 1;
	head = list;
	while (list)
	{
		printf("--- newpath ---\n");
		if (check_visited(list, visited) == FALSE)
			break;
		if (count_turn(info, head, count_path, &curr_turn) == FALSE)
			return (FALSE);
		printf("count_path = %d min_turn = %d curr_turn = %d list->len = %d\n", count_path, *min_turn, curr_turn, list->len);
		if (curr_turn < *min_turn || count_path == 1)
		{
			*min_turn = curr_turn;
			*total_path = count_path;
		}
		else if (curr_turn > *min_turn)
			break;
		count_path++;
		list = list->next;
		printf("\n");
	}
	printf("*total_path = %d min_turn = %d\n", *total_path, *min_turn);
	return (TRUE);
}

void init_nodes(t_info *info)
{
	t_room *room;

	room = info->room_head;
	while (room)
	{
		room->splitted = FALSE;
		room = room->list_next;
	}
}

void	update_visited(t_path *path, t_bool **visited)
{
	int	index;

	index = 1;
	while (index < path->len - 1)
	{
		(*visited)[path->path[index]->index] = TRUE;
		index++;
	}
}

/* run bfs after reverse inverse edges */
t_bool	run_bfs(t_info *info, int count_path, t_path **result_list)
{
	int	index;
	t_path *path_curr;
	t_path *path_next;
	t_bool	*visited;

	index = 0;
	if (create_visited(info, &visited) == FALSE)
		return (FALSE);
	path_curr = NULL;
	if (bfs(info, &path_curr, visited) == FALSE)
		return (FALSE);
	*result_list = path_curr;
	while (index < count_path && path_curr)
	{
		update_visited(path_curr, &visited);
		if (bfs(info, &path_next, visited) == FALSE)
			return (FALSE);
		path_curr->next = path_next;
		path_curr = path_next;
		index++;
	}
	return (TRUE);
}

t_bool get_paths(t_info *info)
=======
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
>>>>>>> origin/itoe_bfs2
{
	t_path *path_curr;
	t_path *path_next;
	t_path *path_head;
<<<<<<< HEAD
	int		count;

	int		min_turn;
	int		curr_turn;

	t_path *result_list;
	int		res_count;
	int		flag;

	count = 1;
	path_curr = NULL;
	result_list = NULL;
	if (get_inverse_edges(info, &path_curr) == FALSE)
		return (FALSE);
	update_link_weight(path_curr);
	path_head = path_curr;
	count_turn(info, path_head, count, &curr_turn);
	min_turn = curr_turn;
	printf("\n--- before while ---\n");
	print_single_path(path_curr);
	res_count = count;
	printf("count_path = %d min = %d curr = %d\n", res_count, min_turn, curr_turn);
	printf("--- while start ---\n");
	flag = TRUE;
	(void)path_next;
	(void)flag;
	(void)result_list;
	/*
	while (path_curr)
	{
		if (get_inverse_edges(info, &path_next) == FALSE)
			return (FALSE);
		print_single_path(path_next);
		if (path_next == NULL)
			break ;
		if (update_link_weight(path_next) == TRUE)
		{
			run_bfs(info, count, &result_list);
			print_paths(result_list);
			count_turn(info, result_list, count, &curr_turn);
			path_curr->next = path_next;
			path_curr = path_next;
			count++;
			res_count = count;
			flag = FALSE;
		}
		else if (flag)
		{
			printf("-- no inverse edge -- \n");
			print_single_path(path_curr);
			print_single_path(path_next);
			path_curr->next = path_next;
			path_curr = path_next;
			count++;
			count_turn(info, path_head, count, &curr_turn);
			if (min_turn > curr_turn)
			{
				min_turn = curr_turn;
				result_list = path_head;
				res_count = count;
			}
			else
				break ;
		}
		printf("count_path = %d min = %d curr = %d\n", count, min_turn, curr_turn);
	}
	printf("--- after while in get_path ---\n");
	printf("res_count = %d min = %d curr = %d\n", res_count, min_turn, curr_turn);
	print_paths(result_list);
	*/
	return (TRUE);
}

t_bool solution(t_info *info)
{
	print_info(info);
	// print_room(info->room_head);
=======

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
>>>>>>> origin/itoe_bfs2
	get_paths(info);
	return (TRUE);
}

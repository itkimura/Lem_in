/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/10/31 14:30:48 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

/* drop edge from a path */
void drop_link(t_link *link, t_room *room)
{
	int index;

	index = 0;
	while (index < room->malloc_link)
	{
		if (room->link[index] == link)
		{
			room->link[index] = NULL;
			break;
		}
		index++;
	}
}

/* upsate the weight of each edge according to a path */
void update_link_weight(t_info *info, t_path *path)
{
	(void)info;
	int i;
	int j;
	t_room *curr;
	t_room *prev;

	i = path->len - 1;
	while (i > 0)
	{
		j = 0;
		curr = path->path[i];
		prev = path->path[i - 1];
		while (j < curr->malloc_link)
		{
			if (curr->link[j] != NULL && (prev == curr->link[j]->room1 || prev == curr->link[j]->room2))
			{
				if (prev == curr->link[j]->room1)
					curr->link[j]->two_one = -1;
				if (prev == curr->link[j]->room2)
					curr->link[j]->one_two = -1;
				drop_link(curr->link[j], prev);
			}
			j++;
		}
		i--;
	}
}
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

/* Initiarize link weight to 1*/
void	init_links(t_info *info)
{
	t_link	*tmp;

	tmp = info->link_head;
	while (tmp)
	{
		tmp->one_two = 1;
		tmp->two_one = 1;
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
void	remove_inverse_edge(t_info *info)
{
	t_link	*curr;
	t_link	*tmp;
	t_link	*next;

	curr = info->link_head;
	while (curr)
	{
		tmp = curr->next;
		if (tmp == NULL)
			break ;
		next = tmp;
		while (tmp->one_two == -1 && tmp->two_one == -1)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		curr->next = next;
		curr = next;
	}
}


void	update_links(t_info *info, t_path *head)
{
	/*make all one_two = 1 & two_one = 1*/
	init_links(info);
	/*update edge weight by bfs result*/
	update_edge_weight(info, head);
	/*remove inverse links*/
	remove_inverse_edge(info);
	/*delete all links and initiarize mallok_link = 0 */
	delete_link_from_room(info);
	/*make all one_two =1 & two_one = 1*/
	init_links(info);
	/*re connect _rooms again*/
	connect_rooms(info);
}

t_bool	best_conbination(t_info *info, t_path *bfs1_list, int *min_turn, int *total_path)
{
	printf("--- second bfs ---\n");
	int		count_path;
	int		curr_turn;
	int		flag;
	t_path	*head;
	t_path	*path_curr;
	t_path	*path_next;

	count_path = 1;
	path_curr = bfs(info);
	head = path_curr;
	flag = FALSE;
	while (path_curr)
	{
		printf("--- newpath ---\n");
		print_single_path(path_curr);
		printf("count_path = %d\n", count_path);
		if (count_turn(info, head, count_path, &curr_turn) == FALSE)
			return (FALSE);
		printf("curr_turn = %d\n", curr_turn);
		if (curr_turn < *min_turn)
		{
			*min_turn = curr_turn;
			flag = TRUE;
			*total_path = count_path;
		}
		update_link_weight(info, path_curr);
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
		count_path++;
		printf("\n");
	}
	printf("min = %d total = %d\n", *min_turn, *total_path);
	printf("--- res --- flag = %d\n", flag);
	t_path	*path;
	path = head;
	if (flag == FALSE)
		path = bfs1_list;
	for(int i = 0; i < *total_path; i++)
	{
		print_single_path(path);
		path = path->next;
	}
	return (TRUE);
}


t_bool	create_visited(t_info *info, t_bool **visited)
{
	*visited = (t_bool *)malloc(sizeof(t_bool) * info->total_rooms);
	if (visited == NULL)
		return (FALSE);
	ft_memset(*visited, FALSE, sizeof(t_bool) * info->total_rooms);
	return (TRUE);
}

t_bool	check_visited(t_path *curr, t_bool *visited)
{
	int		index;

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

t_bool	update_min(t_info *info, t_path *list, int *min_turn, int *total_path)
{
	t_bool	*visited;
	t_path	*head;
	int		count_path;
	int		curr_turn;

	visited = NULL;
	if (create_visited(info, &visited) == FALSE)
		return (FALSE);
	count_path = 1;
	head = list;
	while (list)
	{
		printf("--- newpath ---\n");
		if (check_visited(list, visited) == FALSE)
			break ;
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

/* run the first bfs to find the inverse edge */
t_path *test_maps(t_info *info)
{
	t_path	*path_curr;
	t_path	*path_next;
	t_path	*head;
	
	path_curr = bfs(info);
	head = path_curr;
	while (path_curr)
	{
		update_link_weight(info, path_curr);
		path_next = bfs(info);
		path_curr->next = path_next;
		path_curr = path_next;
	}
	return (head);
}

t_bool	get_paths(t_info *info)
{
	int		min_turn;
	int		total_path;
	t_path	*list;

	/* run bfs first and get the linked list */
	list = test_maps(info);
	print_paths(list);
	/*remove inverse edge*/
	update_links(info, list);
	/* find the conbination in first bfs result*/
	//printf("--- update min ---\n");
	total_path = 0;
	min_turn = 0;
	update_min(info, list, &min_turn, &total_path);
	/*run bfs again to find conbination*/
	best_conbination(info, list, &min_turn, &total_path);
	return (TRUE);
}

t_bool solution(t_info *info)
{
	printf("_____START BFS____\n");
	get_paths(info);
	return (TRUE);
}

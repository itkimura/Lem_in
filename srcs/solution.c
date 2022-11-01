
#include "../includes/lemin.h"




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
/*
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
	path_curr = bfs_test(info);
	print_single_path(path_curr);
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
		path_next = bfs_test(info);
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
*/

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

void	init_nodes(t_info *info)
{
	t_room	*room;

	room = info->room_head;
	while (room)
	{
		room->splitted = FALSE;
		room = room->list_next;
	}
}

/*
 * bfs FALSE = normal bfs, room is splitted
 * bfs TRUE = not normal, room is not splitted and weight = 2
*/
t_path	*best_conbination(t_info *info)
{
	t_path	*path_curr;
	t_path	*path_head;
	t_path	*path_next;

	path_curr = bfs_test(info, TRUE);
	path_head = path_curr;
	while (path_curr)
	{
		path_next = bfs_test(info, TRUE);
		print_single_path(path_curr);
		print_single_path(path_next);
		path_curr->next = path_next;
		path_curr = path_next;
		break ;
	}
	return (path_head);
}

t_bool	get_paths(t_info *info)
{
	t_path	*path_curr;
	t_path	*path_next;
	t_path	*path_head;
	t_path	*list;

	path_curr = bfs_test(info, FALSE);
	print_single_path(path_curr);
	while (1)
	{
		path_curr = bfs_test(info, FALSE);
		print_single_path(path_curr);
		if (path_curr == NULL)
			break ;
		update_link_weight(info, path_curr);
		//print_links(info);
		//remove_inverse_edge(info);
		//printf("-- best --\n");
		//list = best_conbination(info);
		//break ;
		//print_paths(list);
	}
	return (TRUE);

}

t_bool solution(t_info *info)
{
	print_info(info);
	// print_room(info->room_head);
	get_paths(info);
	return (TRUE);
}

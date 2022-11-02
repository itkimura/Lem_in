
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

t_bool get_paths(t_info *info)
{
	t_path *path_curr;
	t_path *path_next;
	t_bool	find_inverse_edge;

	path_curr = NULL;
	if (get_inverse_edges(info, &path_curr) == FALSE)
		return (FALSE);
	print_single_path(path_curr);
	
	update_link_weight(path_curr);
	path_next = NULL;
	if (get_inverse_edges(info, &path_next) == FALSE)
		return (FALSE);
	print_single_path(path_next);
	
	find_inverse_edge = update_link_weight(path_next);
	printf("find_inverse_edge = %d\n", find_inverse_edge);

	t_bool *visited = NULL;
	if (create_visited(info, &visited) == FALSE)
		return (FALSE);
	t_path *path = NULL;
	bfs(info, &path, visited);
	print_single_path(path);

	update_visited(path, &visited);
	bfs(info, &path, visited);
	print_single_path(path);
	/*
	while (1)
	{
		find_inverse_edge = update_link_weight(path_curr);
		if (find_inverse_edge == TRUE)
		{
			printf("find inverse edge!\n");
		}

		count_path++;
	}
	*/
	return (TRUE);
}

t_bool solution(t_info *info)
{
	print_info(info);
	// print_room(info->room_head);
	get_paths(info);
	return (TRUE);
}


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
{
	t_path *path_curr;
	t_path *path_next;
	t_path *path_head;
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
	get_paths(info);
	return (TRUE);
}

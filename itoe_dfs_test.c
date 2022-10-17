#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
path[0]: [b][c][f][g][k][m]
path[1]: [b][c][f][g][j][m]
path[2]: [b][e][h][l][n][m]
path[3]: [b][a][d][i][j][m]
path[4]: [b][e][g][k][m]
path[5]: [b][e][g][j][m]
*/

enum{
	s, //0
	a, //1
	b, //2
	c, //3
	d, //4
	e, //5
	f, //6
	g, //7
	h, //8
	i, //9
	j, //10
	k, //11
	l, //12
	m, //13
	n  //14
};

typedef struct s_sort
{
	int			min;		/* min turn */
	int			*tmp[6];	/* tmp pathset */
	int			*ans[6];	/* current min pathset */
	int			total_path;
	int			source;		/* start_room */
	int			sink;		/* end_room */
	int			quantity_of_ants;
	int			visited[15];
}				t_sort;

void	print_all_path(int array[6][6])
{
	for (int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if (array[i][j] != s)
				printf("%c ", array[i][j] + 'a' - 1);
		}
		printf("\n");
	}
}

void	print_single_path(int array[6])
{
	for(int j = 0; j < 6; j++)
	{
		if (array[j] != s)
			printf("%c ", array[j] + 'a' - 1);
	}
	printf("\n");
}

void	print_ans(int **tmp, int turn)
{
	int	i;
	int	j;

	i = 0;
	while (i < turn)
	{
		printf("path[%d] :", i);
		print_single_path(tmp[i]);
		i++;
	}
	printf("\n");
}

void	print_visited(t_sort *sort)
{
	for (int i = 0; i < 15; i++)
		printf("%d ", sort->visited[i]);
	printf("\n");
}

bool	check_collision(t_sort *sort, int array[6])
{
	int	index;

	index = 1;
	while (index < 6)
	{
		if (sort->visited[array[index]] == 1 && array[index] != sort->sink && array[index] != 0)
			return (false);
		index++;
	}
	return (true);
}

void	update_visited(t_sort *sort, int array[6], bool flag)
{
	int	index;

	//printf("--- update visited --\n");
	//print_visited(sort);
	index = 1;
	while (index < 6)
	{
		if (array[index] != sort->sink && array[index] != 0)
		{
			if (flag == true)
				sort->visited[array[index]] = 1;
			else
				sort->visited[array[index]] = 0;
		}
		index++;
	}
	//print_visited(sort);
	//print_single_path(array);
	//print_ans(sort->tmp, sort->total_path);
	//print_visited(sort);
}

void	update_ans(int turn, t_sort *sort)
{
	int	index;

	index = 0;
	printf("--- update ans ---\n");
	sort->total_path = turn;
	while (index < 6)
	{
		if (index < turn)
			sort->ans[index] = sort->tmp[index];
		else
			sort->ans[index] = 0;
		index++;
	}
	print_ans(sort->ans, turn);
}

void	dfs(int array[6][6], t_sort *sort, int turn)
{
	int	index;
	int	total; /* total lines to traverse all ants.*/

	/* check if the current turn is bigger than min, then end*/
	printf("-- dfs %d --\n", turn);
	print_ans(sort->tmp, turn);
	total = sort->quantity_of_ants / turn + 6 - 2;
	printf("min = %d total = %d turn = %d total_path = %d\n", sort->min, total, turn, sort->total_path);
	//if (total > sort->min && turn > 0)
	//	return ;
	/* if the current turn is smaller than prev turn, update ans*/
	if (sort->min == 0 && turn == 1)
	{
		sort->min = sort->quantity_of_ants / 1 + 6 - 2;
		printf("-------sort min = %d ------------\n", sort->min);
		update_ans(turn, sort);
	}
	else if (total < sort->min)
	{
		sort->min = total;
		update_ans(turn, sort);
	}
	index = turn - 1;
	printf("--- while ---\n");
	while (++index < 6)
	{
		printf("index[%d]: ", index);
		print_single_path(array[index]);
		if (check_collision(sort, array[index]) == false)
			continue ;
		printf("turn = %d\n", turn);
		sort->tmp[turn] = array[index];
		update_visited(sort, array[index], true);
		dfs(array, sort, turn + 1);
		printf("-- return --\n");
		update_visited(sort, array[index], false);
	}
}

int	main(void)
{
	int	array[6][6] = {
		{b, e, g, j, m},
		{b, e, g, k, m},
		{b, a, d, i, j, m},
		{b, e, h, l, n, m},
		{b, c, f, g, j, m},
		{b, c, f, g, k, m},
	};
	t_sort	sort;
	memset(&sort, 0, sizeof(t_sort));
	sort.source = b;
	sort.sink = m;
	sort.quantity_of_ants = 1;
	dfs(array, &sort, 0);
	printf("-- result total_line[%d]-- \n", sort.min);
	print_ans(sort.ans, sort.total_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/11/04 17:41:33 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define FD 0
# include "libft.h"
# include "get_next_line.h"

/* remove later */
# include <stdio.h>

# define NORMAL "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define GREY "\x1B[38;5;238m"
# define PINK "\x1B[38;5;212m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define RATIO 1.5
# define PATH_BUFF_SIZE 100

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

enum
{
	COMMENT,
	ROOM,
	START,
	END,
	COMMAND,
	LINK,
	EMPTY,
};

/* room */
typedef struct s_room
{
	char			*room_name;
	int				index;
	int				total_links;
	int				malloc_link;
	int				path_nb;
	struct s_link	**link;
	struct s_room	*hash_table_next;
	struct s_room	*list_next;
}					t_room;

typedef struct s_que
{
	t_room			*room;
	struct s_que	*next;
}					t_que;

typedef struct s_path {
	t_room			**path;
	// int				at_room;
	int				len;
	struct s_path	*next;
}	t_path;

typedef struct s_result
{
	t_path	*path_head;
	t_path	*tmp_head;
	t_path	*best_paths;
	int		min_turn;
	int		curr_turn;
	int		total; //total paths that we are using for res
	int		**divide_ants;
} t_result;


/* link-room structure */
/*
 * one_two -> the weight from room 1 to room 2
 * two_one -> the weight from room 2 to room 1
 */
typedef struct s_link
{
	t_room			*room1;
	t_room			*room2;
	int				one_two;
	int				two_one;
	struct s_link	*next;
}					t_link;

/* adjacency matrix */
typedef struct s_info
{
	int		total_ants;
	int		total_rooms;
	int		total_links;
	t_room	*start_room;
	t_room	*end_room;
	char	*line;
	t_room	*room_head;
	t_room	**hash_table;
	t_link	*link_head;
}			t_info;

/* bfs */
typedef struct s_bfs
{
	t_que	*head;
	t_que	*tail;
	t_bool	*visited;
	t_room	***prev;
}	t_bfs;

/* bfs.c */
t_path			*bfs(t_info *info);

/* bfs_free.c */
void			free_bfs(t_bfs *b, int	malloc_link);
void			free_path(t_path *path);
void			free_paths(t_path *path);
void			free_que(t_que *head);

/* bfs_utils.c */
t_room			*pop(t_que **head);
void			push(t_que **tail, t_que **head, t_que *new);
t_que			*create(t_room *room);

/* count_turn.c */
t_bool			init_path_array(t_path *list, int count_path, int ***path);
void			devide_ants(t_info *info, int ***path, int count_path);
t_bool			count_turn(t_info *info, t_result *result, int count_path);
void			free_divide_ants_array(int ***path, int count_path);

/* solution.c */
t_bool			solution(t_info *info);

/* lem-in.c */
t_bool			init_info(t_info *info);
t_bool			check_digit_and_space(char *line);
t_bool			check_xy(char *line);
t_bool			lem_in(void);

/* hash_table.c */
unsigned int	hash(char *str, int size);
t_bool			create_hash_table(t_info *info);
t_room			*hash_table_lookup(t_room **hash_table, char *str, int size);
t_bool			hash_table_appending(t_info *info, t_room *list);
t_bool			init_hash_table(t_info *info);

/* utils.c */
void			error(char *error);
void			free_rooms(t_room **head);
void			free_links(t_link **link);

/* print.c */
void			print_hash_table(t_info *info);
void			print_single_room(t_room *room);
void			print_rooms(t_room *room);
void			print_info(t_info *info);
void			print_single_path(t_path	*path);
void			print_paths(t_path *path);
void			print_single_link(t_link *link);
void			print_links(t_info *info);
char			room_name_index(int index);
void			printing_bfs(t_info *info, t_bfs *b);
void			print_que(t_que *head, t_bfs *b);

/* validation/read_line.c */
int				type_of_line(char *str);
t_bool			get_ants(t_info *info, int type, int *stage);
t_bool			path_to_each_stage(t_info *info, int type, int *stage);
t_bool			read_line(t_info *info);

/* validation/create_room.c */
t_bool			create_new_room(t_room **room, t_info *info);
char			*get_room_name(char *line);
t_bool			get_rooms(t_info *info, int type);

/* validation/create_link.c */
t_bool			get_room_in_link(t_link *new, t_room **hash_table,
					char *line, int size);
t_bool			create_new_link(t_info *info);
t_bool			get_links(t_info *info);

/* validation/onnect_rooms.c */
void			create_link_array(t_info *info);
t_bool			connect_rooms(t_info *info);

#endif

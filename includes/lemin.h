/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/11/08 16:45:08 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define FD 0
#include "libft.h"
#include "get_next_line.h"

/* remove later */
#include <stdio.h>
#include <stdlib.h>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define GREY "\x1B[38;5;238m"
#define PINK "\x1B[38;5;212m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define RATIO 1.5
#define PATH_BUFF_SIZE 100

typedef enum e_bool
{
	FALSE,
	TRUE,
} t_bool;

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

enum
{
	INVERSE = -1,
	UNUSED,
	DROP
};

enum
{
	PATH_LEN,
	ANTS
};

/* room */
typedef struct s_room
{
	char *room_name;
	int index;
	int total_links;
	int malloc_link;
	int path_nb;
	t_bool is_occupied;
	struct s_link **link;
	struct s_room *hash_table_next;
	struct s_room *list_next;
} t_room;

typedef struct s_que
{
	t_room *room;
	struct s_que *next;
} t_que;

typedef struct s_path
{
	t_room **path;
	// int				at_room;
	int len;
	struct s_path *next;
} t_path;

typedef struct s_result
{
	t_path *path_head;
	t_path *tmp_head;
	t_path *best_paths;
	int min_turn;
	int curr_turn;
	int total; // total paths that we are using for res
	int **divide_ants;
} t_result;

typedef struct s_ants
{
	char *nbr;
	t_path *path;
	int pos;
} t_ants;

/* link-room structure */
/*
 * one_two -> the weight from room 1 to room 2
 * two_one -> the weight from room 2 to room 1
 */
typedef struct s_link
{
	t_room *room1;
	t_room *room2;
	int one_two;
	int two_one;
	struct s_link *link_hash_table_next;
	struct s_link *next;
} t_link;

/* adjacency matrix */
typedef struct s_info
{
	int total_ants;
	int total_rooms;
	int total_links;
	t_room *start_room;
	t_room *end_room;
	char *line;
	t_room *room_head;
	t_link *link_head;
	t_room **hash_table;
	t_link **link_hash_table;
} t_info;

/* bfs */
typedef struct s_prev
{
	t_room **path;
	t_bool inverse;
} t_prev;

typedef struct s_bfs
{
	t_que *head;
	t_que *tail;
	t_bool *visited;
	t_prev **prev;
} t_bfs;

/* bfs.c */
t_bool bfs(t_info *info, t_path **path, t_bool flag);

/* bfs_free.c */
void free_bfs(t_bfs *b, int malloc_link);
void free_path(t_path *path);
void free_paths(t_path *path);
void free_que(t_que *head);

/* bfs_init.c */
void init_path(t_room **path, int size);
t_bool init_prev(t_info *info, t_bfs *b);
void init_visited(t_bool *visited, int size);
t_bool init_bfs(t_info *info, t_bfs *b);

/* bfs_utils.c */
t_room *pop(t_que **head);
void push(t_que **tail, t_que **head, t_que *new);
t_que *create(t_room *room);
t_bool	push_and_update(t_bfs *b, t_room *curr, t_room *next, t_bool is_inverse);

/* bfs_reverse_path.c */
t_bool get_path_len(t_info *info, t_room **prev, t_path *path);
t_bool reverse_path(t_info *info, t_room **prev, t_path **path);

/* count_turn.c */
void devide_ants(t_info *info, int ***path, int count_path);
t_bool count_turn(t_info *info, t_result *result, int count_path);

/* update_link.c */
t_bool update_link_weight(t_info *info, t_path *head);
void init_unused_links(t_info *info, t_path *head);

/* solution.c */
t_bool solution(t_info *info);

/* lem-in.c */
t_bool init_info(t_info *info);
t_bool lem_in(void);

/* room_hash_table.c */
unsigned int hash(char *str, int size);
t_bool create_room_hash_table(t_info *info);
t_room *room_hash_table_lookup(t_room **hash_table, char *str, int size);
t_bool room_hash_table_appending(t_info *info, t_room *list);
t_bool init_room_hash_table(t_info *info);

/* link_hash_table.c */
t_bool create_link_hash_table(t_info *info, int size);
t_link *link_hash_table_lookup(t_link **link_hash_table, int index_1, int index_2, int size);
t_bool link_hash_table_appending(t_info *info, t_link *list, int size);
t_bool init_link_hash_table(t_info *info);

/* utils.c */
void free_rooms(t_room **head);
void free_links(t_link **link);
void free_divide_ants_array(int ***path, int count_path);
void free_ants(t_ants **ants, int total_ants);

/* print.c */
void print_ant(char *ant, char *room_name);
void print_error(char *print_error);

void print_hash_table(t_info *info);
void print_single_room(t_room *room);
void print_rooms(t_room *room);
void print_info(t_info *info);
void print_single_path(t_path *path);
void print_paths(t_path *path);
void print_single_link(t_link *link);
void print_links(t_info *info);
char room_name_index(int index);
void printing_bfs(t_info *info, t_bfs *b);
void print_que(t_que *head, t_bfs *b);
void print_matrix(t_info *info);

/* validation/read_line.c */
int type_of_line(char *str);
t_bool get_ants(t_info *info, int type, int *stage);
t_bool path_to_each_stage(t_info *info, int type, int *stage);
t_bool read_line(t_info *info, t_bool flag);

/* validation/create_room.c */
t_bool create_new_room(t_room **room, t_info *info);
char *get_room_name(char *line);
t_bool get_rooms(t_info *info, int type);

/* validation/create_link.c */
t_bool get_room_in_link(t_link *new, t_room **hash_table,
						char *line, int size);
t_bool create_new_link(t_info *info);
t_bool get_links(t_info *info);

/* validation/connect_rooms.c */
void create_link_array(t_info *info);
t_bool connect_rooms(t_info *info);

/* validation/validation_utils.c */
t_bool check_digit_and_space(char *line);
t_bool check_xy(char *line);

/* print_ants.c */
t_bool mangage_ants(t_result *result, t_info *info);

#endif

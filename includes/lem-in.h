/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/10/04 17:20:14 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h> //rmb to delete
# include "libft.h"
# include "get_next_line.h"

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define FD 0

typedef enum {
	FALSE,  // 0
	TRUE,  // 1
} e_bool;

enum{
	COMMENT,
	ROOM,
	START,
	END,
	COMMAND,
	LINK,
};

/* room */
typedef struct	s_room {
	char	*room_name; //to check if it's the same room
	int		index;
	int		link_number;
	int		malloc_link;
	struct s_room	**link;
	struct s_room  *next;
}				t_room;

/* adjacency matrix */
typedef	struct s_info
{
	int		quantity_of_ants;
	int		quantity_of_rooms; // needed for adjacency matrix
	char	*start_room;
	char	*end_room;
	char	*line;
	t_room	*room_head;
	t_room	**hash_table;
}			t_info;

/* link-room structure */
typedef	struct s_link_room
{
	char				*line;
	struct s_link_room	*next;
}						t_link_room;


/* read_line.c */
e_bool read_line(t_info *info);
e_bool get_ants(t_info *info , int type, int *stage);
int type_of_line(char *str);
e_bool	path_to_each_stage(t_info *info, int type, int *stage);

/* create_room.c */
char *get_room_name(char *line);
e_bool get_rooms(t_info *info, int type);
e_bool create_new_room(t_room **room, t_info *info);

/* create_link */


/* hash_table.c */
e_bool	init_hash_table(t_info *info);
e_bool	hash_table_appending(t_info *info, t_room *list);
e_bool	create_hash_table(t_info *info);
int		hash(char *str, int size);

/* lem-in.c */
e_bool	lem_in();
e_bool	check_xy(char *line);
e_bool	check_digit_and_space(char *line);
e_bool	init_info(t_info *info);

/* utils.c */
void free_rooms(t_room **head);
void print_room(t_room *room);
void print_info(t_info *info);
void	error(char *error);
void print_hash_table(t_info *info);


#endif

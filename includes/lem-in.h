/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/10/03 14:40:56 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h> //rmb to delete
# include "libft.h"

// # define INT_MAX 2147483647
// # define INT_MIN -2147483648
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
	struct s_room  *next;
}				t_room;

/* adjacency matrix */
typedef	struct s_info
{
	int		quantity_of_ants;
	int		quantity_of_rooms; // needed for adjacency matrix
	char	**name_of_room; // numbering the room but keep name in char array E.g. [0]->room1 [1]->room2
	char	*start_room;
	char	*end_room;
	char	**matrix;
	char	*line;
	t_room	*room_head;
	t_room	*tmp;
}			t_info;


/* read_line.c */
e_bool read_line(t_info *info);
e_bool get_ants(t_info *info , int type, int *stage);
e_bool get_rooms(t_info *info, int type, int *stage, int *command);
char *get_room_name(char *line);
int type_of_line(char *str);
e_bool is_positive(int nb);
e_bool create_new_room(t_room **room, t_info *info);
void print_info(t_info *info);

/* lem-in.c */
e_bool	lem_in();
e_bool	check_xy(char *line);
e_bool	check_digit_and_space(char *line);
e_bool	init_info(t_info *info);
void	error(char *error);
void print_room(t_room *room);

/* utils.c */
void free_rooms(t_room **head);
void print_room(t_room *room);
e_bool is_positive(int nb);
void print_info(t_info *info);
void	error(char *error);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/10/05 11:02:48 by thle             ###   ########.fr       */
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
};

/* room */
typedef struct s_room
{
	char			*room_name;
	int				index;
	int				link_number;
	int				malloc_link;
	struct s_room	**link;
	struct s_room	*next;
}					t_room;

/* adjacency matrix */
typedef struct s_info
{
	int			quantity_of_ants;
	int			quantity_of_rooms;
	char		*start_room;
	char		*end_room;
	char		*line;
	t_room		*room_head;
	t_room		**hash_table;
}				t_info;

/* link-room structure */
typedef struct s_link_room
{
	char				*line;
	struct s_link_room	*next;
}						t_link_room;

/* read_line.c */
t_bool		read_line(t_info *info);
t_bool		get_ants(t_info *info, int type, int *stage);
int			type_of_line(char *str);
t_bool		path_to_each_stage(t_info *info, int type, int *stage);

/* create_room.c */
char		*get_room_name(char *line);
t_bool		get_rooms(t_info *info, int type);
t_bool		create_new_room(t_room **room, t_info *info);

/* create_link */

/* hash_table.c */
t_bool		init_hash_table(t_info *info);
t_bool		hash_table_appending(t_info *info, t_room *list);
t_bool		create_hash_table(t_info *info);
t_room		*hash_table_lookup(t_room **hash_table, char *str, int size);
int			hash(char *str, int size);

/* lem-in.c */
t_bool		lem_in(void);
t_bool		check_xy(char *line);
t_bool		check_digit_and_space(char *line);
t_bool		init_info(t_info *info);

/* utils.c */
void		free_rooms(t_room **head);
void		print_room(t_room *room);
void		print_info(t_info *info);
void		error(char *error);
void		print_hash_table(t_info *info);

#endif

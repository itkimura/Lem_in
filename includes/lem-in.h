/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 14:54:48 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h> //rmb to delete
# include "libft.h"
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef enum {
    FALSE,  // 0
    TRUE,  // 1
} e_bool;

enum{
	ROOM,
	START,
	END,
	COMMENT,
	COMMAND,
};

/* adjacency matrix */
typedef	struct s_info
{
	int		quantity_of_ants;
	int		quantity_of_rooms; // needed for adjacency matrix
	char	**name_of_room; // numbering the room but keep name in char array E.g. [0]->room1 [1]->room2
	int		start_room;
	int		end_room;
	char	**matrix;
}			t_info;

/* room check unique coord */
typedef struct	s_room {
	int				type;
	int				x;
	int				y;
	char			*room_name; //to check if it's the same room
	struct s_room  *next;
}				t_room;

#endif

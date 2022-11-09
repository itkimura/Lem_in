# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/11/09 11:44:36 by thle             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = lem-in

DEBUG_FLAG = -g

INCLUDES_DIR = ./includes/


SRCS_DIR = ./srcs/
FILES = lem-in.c	free_utils.c	print.c	
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

VALIDATION_DIR =	./srcs/validation/
VALIDATION_FILES =	validation_utils.c		connect_rooms.c		\
					create_link.c			create_room.c		\
					read_line.c		

BFS_DIR =	./srcs/bfs/
BFS_FILES =	bfs.c			bfs_utils.c		bfs_free.c		\
			bfs_init.c		bfs_reverse_path.c

HASH_TABLE_DIR =	./srcs/hash_table/
HASH_TABLE_FILES =	link_hash_table.c	room_hash_table.c

SOLUTION_DIR =		./srcs/solution/
SOLUTION_FILES =	solution.c				count_turn.c	\
					print_ants.c			update_link.c

LIBFT_DIR =		./srcs/libft/
LIBFT_FILES =	ft_atol.c		ft_itoa.c		\
				ft_strcpy.c		ft_strcat.c		\
				ft_strchr.c		ft_strdel.c		\
				ft_isdigit.c	ft_putstr_fd.c	\
				ft_strcmp.c		ft_strsub.c		\
				ft_strlen.c		get_next_line.c	\
				ft_strdup.c		ft_strjoin.c

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))
VALIDATION_OBJS = $(addprefix $(OBJS_DIR), $(VALIDATION_FILES:%.c=%.o))
BFS_OBJS = $(addprefix $(OBJS_DIR), $(BFS_FILES:%.c=%.o))
HASH_TABLE_OBJS = $(addprefix $(OBJS_DIR), $(HASH_TABLE_FILES:%.c=%.o))
SOLUTION_OBJS = $(addprefix $(OBJS_DIR), $(SOLUTION_FILES:%.c=%.o))
LIBFT_OBJS = $(addprefix $(OBJS_DIR), $(LIBFT_FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(NAME)

$(NAME):	$(OBJS_DIR)			\
			$(LIBFT_OBJS)		\
			$(OBJS)				\
			$(VALIDATION_OBJS)	\
			$(HASH_TABLE_OBJS)	\
			$(BFS_OBJS)			\
			$(SOLUTION_OBJS)
	@$(CC) $(FLAGS) -o $(NAME)	\
			$(LIBFT_OBJS)		\
			$(OBJS)				\
			$(VALIDATION_OBJS)	\
			$(HASH_TABLE_OBJS)	\
			$(BFS_OBJS)			\
			$(SOLUTION_OBJS)
	@echo "Compiled $(NAME)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(VALIDATION_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(BFS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"
	
$(OBJS_DIR)%.o: $(HASH_TABLE_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"
	
$(OBJS_DIR)%.o: $(SOLUTION_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(LIBFT_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@
	@echo "Compiled $@"

clean:
	@/bin/rm -rf $(OBJS_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

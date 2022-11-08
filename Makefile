# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thule <thule@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/11/08 18:18:06 by thule            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = lem-in

DEBUG_FLAG = -g

INCLUDES_DIR = ./includes/

FILES = lem-in.c	free_utils.c	print.c	
		

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

VALIDATION_DIR = ./srcs/validation/
VALIDATION_FILES =	validation_utils.c		connect_rooms.c		\
					create_link.c			create_room.c		\
					read_line.c		

BFS_DIR =	./srcs/bfs/
BFS_FILES =	bfs.c			bfs_utils.c		bfs_free.c		\
			bfs_init.c		bfs_reverse_path.c

HASH_TABLE_DIR =	./srcs/hash_table/
HASH_TABLE_FILES =	link_hash_table.c	room_hash_table.c

SOLUTION_DIR =		./srcs/solution/
SOLUTION_FILES =	solution.c				count_turn.c \
					print_ants.c			update_link.c


OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))
VALIDATION_OBJS = $(addprefix $(OBJS_DIR), $(VALIDATION_FILES:%.c=%.o))
BFS_OBJS = $(addprefix $(OBJS_DIR), $(BFS_FILES:%.c=%.o))
HASH_TABLE_OBJS = $(addprefix $(OBJS_DIR), $(HASH_TABLE_FILES:%.c=%.o))
SOLUTION_OBJS = $(addprefix $(OBJS_DIR), $(SOLUTION_FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(NAME)

$(NAME): $(OBJS_DIR) $(VALIDATION_OBJS) $(BFS_OBJS) $(OBJS) $\
		$(HASH_TABLE_OBJS) $(SOLUTION_OBJS) $(LIB)
	@$(CC) $(DEBUG_FLAG) -o $(NAME) $(FLAGS) $(VALIDATION_OBJS) $(BFS_OBJS) $\
			$(OBJS) $(HASH_TABLE_OBJS) $(SOLUTION_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(NAME)"

$(LIB):
	@$(MAKE) -sC ./libft
	@echo "Compiled $(LIB)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(VALIDATION_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(BFS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"
	
$(OBJS_DIR)%.o: $(HASH_TABLE_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"
	
$(OBJS_DIR)%.o: $(SOLUTION_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

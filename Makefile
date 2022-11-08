# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thule <thule@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/11/08 13:35:52 by thule            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = lem-in

DEBUG_FLAG = -g

INCLUDES_DIR = ./includes/

FILES = lem-in.c utils.c hash_table.c \
		print.c			\
		bfs.c					bfs_utils.c				bfs_free.c		\
		solution.c				count_turn.c			print_ants.c	\
		bfs_init.c				link_hash_table.c		update_link.c 



SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

VALIDATION_DIR = ./srcs/validation/
VALIDATION_FILES = validation_utils.c connect_rooms.c	create_link.c	\
					create_room.c	read_line.c		

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))
VALIDATION_OBJS = $(addprefix $(OBJS_DIR), $(VALIDATION_FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(NAME)

$(NAME): $(OBJS_DIR) $(VALIDATION_OBJS) $(OBJS) $(LIB)
	@$(CC) $(DEBUG_FLAG) -o $(NAME) $(FLAGS) $(VALIDATION_OBJS) $(OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(NAME)"

$(LIB): #$(wildcard libft/srcs/*.c)
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

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

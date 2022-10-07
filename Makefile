# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/10/07 10:39:33 by itkimura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
# FLAGS = 
NAME = lem-in

DEBUG_FLAG = -g

INCLUDES_DIR = ./includes/

FILES = lem-in.c read_line.c		utils.c hash_table.c	create_room.c	\
		create_link.c				connect_rooms.c			print.c

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(FILES))


OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(DEBUG_FLAG) -o $(NAME) $(FLAGS) $(OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(NAME)"

$(LIB): #$(wildcard libft/srcs/*.c)
	@$(MAKE) -sC ./libft
	@echo "Compiled $(LIB)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

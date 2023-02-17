# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 18:39:31 by jvigny            #+#    #+#              #
#    Updated: 2023/02/17 16:27:43 by jvigny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
NAME_DEBUG = philosophers_debug

CC = gcc
CFLAGS =  -Wall -Werror -Wextra -g3
DEBUG = -fsanitize=thread
LFLAGS = -lpthread
INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST = philosophers.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = action_philo.c	fill_print.c	ft_usleep.c	n_time.c	time.c \
			free_str.c	ft_strdup.c	parsing.c \
			ft_atoi.c	init.c	philosophers.c

SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

	
OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

OBJ_DIR_DEBUG = ./obj_debug/
OBJ_LIST_DEBUG = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ_DEBUG = $(addprefix $(OBJ_DIR_DEBUG), $(OBJ_LIST_DEBUG))


all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
debug:	$(NAME_DEBUG)

$(NAME_DEBUG):	$(OBJ_DIR_DEBUG) $(OBJ_DEBUG)
	$(CC) $(INCLUDES) $(LFLAGS) $(OBJ_DEBUG) -o $(NAME_DEBUG)

$(OBJ_DIR_DEBUG)%.o:	$(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(DEBUG) -c $(INCLUDES) $< -o $@

$(OBJ_DIR_DEBUG):
	mkdir -p $(OBJ_DIR_DEBUG)	

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re

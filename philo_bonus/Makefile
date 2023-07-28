# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 18:39:31 by jvigny            #+#    #+#              #
#    Updated: 2023/07/28 14:23:43 by jvigny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lpthread
INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST = philo.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = action_philo.c	fill_print.c	n_time.c	time.c \
			free_str.c	ft_strdup.c	parsing.c \
			ft_atoi.c	init.c	philosophers.c	check_death.c ft_strjoin.c \
			ft_itoa.c	close.c

SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

	
OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re

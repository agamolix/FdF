# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:07:37 by atrilles          #+#    #+#              #
#    Updated: 2022/05/24 14:03:44 by atrilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######## PROJECT ###############################################################

NAME = fdf

######## DIRECTORIES ###########################################################

SRC_DIR	= src/

######## SOURCE FILES ##########################################################

SRC_FILES =		fdf		gnl		gnl_utils 	trace_line 	coord \
				split	atoi	init		color		keys \
				bresenham1234	bresenham5678	bresenhamUDLR 	utils		

SRC = $(addprefix src/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix src/, $(addsuffix .o, $(SRC_FILES)))

######## FLAGS #################################################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 

######## RULES #################################################################

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

.PHONY: clean fclean re

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

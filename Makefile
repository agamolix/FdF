# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrilles <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:07:37 by atrilles          #+#    #+#              #
#    Updated: 2022/02/16 18:17:53 by atrilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######## PROJECT ###############################################################

NAME = fdf

######## DIRECTORIES ###########################################################

SRC_DIR	= src/

######## SOURCE FILES ##########################################################

SRC_FILES =		fdf		gnl		gnl_utils 	trace_line 	coord \
				split	atoi	init		color		keys \
				bresenham1234	bresenham5678	bresenhamUDLR		

SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))

######## FLAGS #################################################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 

######## RULES #################################################################

all: $(NAME)

$(NAME): $(OBJ)
#	$(CC) $(OBJ) -Lminilibx -lminilibx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz -o $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -lm -lbsd -lmlx -lXext -lX11 -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Iminilibx -O3 -c $< -o $@

.PHONY: clean fclean re

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

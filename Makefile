# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/03 15:30:43 by pivanovi          #+#    #+#              #
#    Updated: 2014/04/21 19:45:22 by pivanovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC =		src/philo.c									\
			src/set_and_co.c							\
			src/sticks_and_stones.c

OBJ = $(SRC:.c=.o)

CFLAGS += -I./includes -I /usr/X11/include
LIBX = -L /usr/X11/lib -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBX)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

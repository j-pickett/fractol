# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apickett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/29 15:17:25 by apickett          #+#    #+#              #
#    Updated: 2019/02/26 17:22:50 by apickett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol 
CC = gcc
SRC = 	main.c \
		ft_rgb.c \
		ft_hooks.c \
		ft_fractols.c \
		ft_assignment.c
OBJ = $(SRC:.c=.o) 
CFLAGS =  -Wall -Wextra -Werror
LIBDIR = -L./libft -L./minilibx_macos
LIBS = -lft -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) libft/libft.a minilibx_macos/libmlx.a fractol.h 
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBDIR) $(LIBS)

libft/libft.a:
	make -C ./libft

minilibx_macos/libmlx.a:
	make -C ./minilibx_macos

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

lclean:
	make fclean -C ./libft
	make clean -C ./minilibx_macos

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 16:28:20 by nandreev          #+#    #+#              #
#    Updated: 2024/11/21 19:48:34 by mkokorev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = src/main.c src/free.c src/read_map.c src/check_map.c src/characters_and_player_check.c src/get_textures.c src/scene_elements.c\
		src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c\
		src/raycasting.c src/draw.c src/window_manage.c

OBJS := $(SOURCES:.c=.o)
MLX_LIB = mlx/
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -d "mlx" ]; then \
	git clone https://github.com/42Paris/minilibx-linux.git mlx; \
	fi
	@make -C $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(GETNEXTLINE) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

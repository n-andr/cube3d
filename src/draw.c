#include "../cube3d.h"

void	ft_texture_coord_def(t_game_info *game, t_line line, int *x, int *y)
{
	int		col;
	int		wall_up_part;

	col = line.x / CELL_SIZE;
	*x = (game->textures.width * (line.x - col * CELL_SIZE)) / ((col + 1) * CELL_SIZE);
	wall_up_part = line.y1 - line.y_top;
	*y = wall_up_part * game->textures.height / line.high;
	*x = line.offset_x *game->textures.width / CELL_SIZE;
}

unsigned int ft_get_pixel_color(t_game_info	*game, t_line line, int x, int y)
{
	int bytes_per_pixel;
	char *pixel;
	unsigned int color;

	bytes_per_pixel = game->textures.bpp / 8;
	/*printf("line.w_wall_side: %d\n", line.w_wall_side);
	printf("line.e_wall_side: %d\n", line.e_wall_side);
	printf("line.s_wall_side: %d\n", line.s_wall_side);
	printf("line.n_wall_side: %d\n", line.n_wall_side);*/
	if (line.w_wall_side)
		pixel = game->textures.w_data + (y * game->textures.size_line) + (x * bytes_per_pixel);
	else if (line.s_wall_side)
		pixel = game->textures.s_data + (y * game->textures.size_line) + (x * bytes_per_pixel);
	else if (line.n_wall_side)
		pixel = game->textures.n_data + (y * game->textures.size_line) + (x * bytes_per_pixel);
	else if (line.e_wall_side)
		pixel = game->textures.e_data + (y * game->textures.size_line) + (x * bytes_per_pixel);

	// Combine bytes into a full color value depending on endianness.
	color = *(unsigned int *)pixel;
	return color;
}

void	ft_dot_draw(t_game_info *game, t_line line, unsigned int color)
{
    char			*dst;
	int				x;
	int				y;

    	//printf("x: %d, y1: %d\n", lines.x, lines.y1);
	x = 0;
	y = 0;
    dst = game->drawing_data.addr + (line.y1 * game->drawing_data.line_length
            + line.x * (game->drawing_data.bits_per_pixel / 8));
	ft_texture_coord_def(game, line, &x, &y);
	if (!color)
		color = ft_get_pixel_color(game, line, x, y);
    *(unsigned int *)dst = color;
}

void	ft_draw_vertikal(t_game_info *game, t_line line, unsigned int color)
{
	line.y_top = line.y1;
	if (line.y1 < 0)
		line.y1 = 0;
	if (line.y2 > S_H)
		line.y2 = S_H;
	while (abs(line.y1 - line.y2) > 0)
	{
		ft_dot_draw(game, line, color);
		line.y1 = line.y1 + 1;
	}
	//ft_dot_draw(game, line, color);
	return ;
}

void	draw_cell(int x, int y, int color, t_game_info *game)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = x * MINI_CELL_SIZE;
	start_y = y * MINI_CELL_SIZE;
	i = 0;
	while (i < MINI_CELL_SIZE)
	{
		j = 0;
		while (j < MINI_CELL_SIZE)
		{
			mlx_pixel_put(game->mlx, game->window, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game_info *game, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = (game->player.x / (CELL_SIZE / MINI_CELL_SIZE)) - (PLAYER_SIZE / 2);
	start_y = (game->player.y / (CELL_SIZE / MINI_CELL_SIZE)) - (PLAYER_SIZE / 2);
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_pixel_put(game->mlx, game->window, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
	//printf("mini: start x: %d, start y: %d\n", start_x, start_y);
	//printf("mini: player center x: %d, player center y: %d\n", (game->player.x / (CELL_SIZE / MINI_CELL_SIZE)), (game->player.y / (CELL_SIZE / MINI_CELL_SIZE)));
}

void	render_map(t_game_info *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == ' ')
				draw_cell(x, y, 0x000000, game); // Black for nothing
			else if (game->map[y][x] == '1')
				draw_cell(x, y, 0x696969, game); // gray for walls
			else if (game->map[y][x] == '0')
				draw_cell(x, y, 0xFFFFFF, game); // White for empty spaces
			else if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E' || game->map[y][x] == 'W')
				//draw_cell(x, y, 0x00FF00, game); // Green for player
				draw_cell(x, y, 0xFFFFFF, game); // White for players cell
			x++;
		}
		y++;
	}
	draw_player(game, 0x0000FF); // blue for player position
}

// top-down view

/*
119 - W
115 - S
100 - D
97 - A

65361 - left arrow
65363 - right arrow

65307 - esc
*/
int	key_pressed(int key, t_game_info *game)
{
	int	i;

	if (key == 119 || key == 115 \
	|| key == 100 || key == 97)
	{
		move_p(game, key);
	}
	else if (key == 65361 || key == 65363)
	{
		turn_p(game, key);
	}
	else if (key == 65307)
	{
		close_game(game, 0);
	}
		ft_memset(game->drawing_data.addr, 0, S_W * S_H * sizeof(int));
	ft_raycasting(game);
	ft_floor_ceiling_colour(game);
   	i = 0;
    while (i < S_W)
      {
    	ft_draw_vertikal(game, game->lines[i], 0);
        i++;
      }
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0, 0);
	//test_texture_render(game); // for testing outputs textures
	render_map(game); // update visuals and minimap
	return (0);
}

void	ft_floor_ceiling_colour (t_game_info *game)
{
	int				i;
	t_line			line;
	unsigned int	color;

	i = 0;
	while (i < S_W)
	{
		line.x = i;
		line.y1 = 0;
		line.y2 = S_H / 2;
		color = game->textures.ceiling;
		ft_draw_vertikal(game, line, color);
		line.y1 = S_H / 2;
		line.y2 = S_H;
		color = game->textures.floor;
		ft_draw_vertikal(game, line, color);
		i++;
	}
}

void	ft_game_draw(t_game_info *game)
{
	int				i;

	game->window = mlx_new_window(game->mlx, S_W,
		S_H, "Cube3D");
	game->drawing_data.img = mlx_new_image(game->mlx, S_W, S_H);
	game->drawing_data.addr = mlx_get_data_addr(game->drawing_data.img,
		&game->drawing_data.bits_per_pixel,
			&game->drawing_data.line_length, &game->drawing_data.endian);
	ft_floor_ceiling_colour(game);
	i = 0;
	while (i < S_W)
	{
		ft_draw_vertikal(game, game->lines[i], 0);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0, 0);
	render_map(game);
	//test_texture_render(game);
	// printf("(before move) p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	// printf("(before move) x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	// printf("(before move) angle: %f \n", game->player.p_angle); //debug

	mlx_key_hook(game->window, key_pressed, game);
	mlx_hook(game->window, 17, 1L << 17, x_close, &game);
	mlx_loop(game->mlx);
}

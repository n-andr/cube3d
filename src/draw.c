#include "../cube3d.h"

void	ft_dot_draw(t_data data, t_line lines)
{
    char	*dst;

    	//printf("x: %d, y1: %d\n", lines.x, lines.y1);
    dst = data.addr + (lines.y1 * data.line_length
            + lines.x * (data.bits_per_pixel / 8));
    *(unsigned int *)dst = lines.color;
}

void	ft_draw_vertikal(t_game_info *game, t_line lines)
{

	while (abs(lines.y1 - lines.y2) > 0)
	{
        //if (lines.high < S_H)
        ft_dot_draw(game->drawing_data, lines);
		lines.y1 = lines.y1 + 1;
	}
	ft_dot_draw(game->drawing_data, lines);
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

void	render_minimap(t_game_info *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x + 1])
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

// void	update_minimap(t_game_info *game)
// {
// 	draw_player(game, 0x0000FF); // blue for player position
// }

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
int	key_pressed(int key, t_game_info *game) // not used
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
   	i = 0;
    while (i < S_W)
      {
    	ft_draw_vertikal(game, game->lines[i]);
        i++;
      }
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0, 0);
	// update_mimimap(game); // update visuals and minimap
	draw_player(game, 0x0000FF); // draw new player position on minimap
	return (0);
}

int key_press(int key, t_game_info *game)
{
	//add multiple key press
	if (key == KEY_W)
		game->key_state.key_w = 1;
	else if (key == KEY_S)
		game->key_state.key_s = 1;
	else if (key == KEY_D)
		game->key_state.key_d = 1;
	else if (key == KEY_A)
		game->key_state.key_a = 1;
	else if (key == KEY_LEFT)
		game->key_state.key_left = 1;
	else if (key == KEY_RIGHT)
		game->key_state.key_right = 1;
	else if (key == KEY_ESC)
		close_game(game, 0);
	return (0);
}

int	key_release(int key, t_game_info *game)
{
	//add multiple key release
	if (key == KEY_A || key == KEY_D \
	|| key == KEY_S || key == KEY_W)
	{
		game->key_state.key_w = 0;
		game->key_state.key_s = 0;
		game->key_state.key_a = 0;
		game->key_state.key_d = 0;
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		game->key_state.key_left = 0;
		game->key_state.key_right = 0;
	}
	return (0);
}

int render_and_update(t_game_info *game)
{
	int	i;

	if (game->key_state.key_w)
		move_p(game, KEY_W);
	if (game->key_state.key_s)
		move_p(game, KEY_S);
	if (game->key_state.key_d)
		move_p(game, KEY_D);
	if (game->key_state.key_a)
		move_p(game, KEY_A);
	if (game->key_state.key_left)
		turn_p(game, KEY_LEFT);
	if (game->key_state.key_right)
		turn_p(game, KEY_RIGHT);
	ft_memset(game->drawing_data.addr, 0, S_W * S_H * sizeof(int));
	ft_raycasting(game);
	i = 0;
	while (i < S_W)
	{
		ft_draw_vertikal(game, game->lines[i]);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0, 0);
	//render_minimap(game); // update visuals and minimap
	return (0);
}

void	ft_game_draw(t_game_info *game)
{
	//void			*mlx_win;
    //t_data			img;
    //t_vars			data;
    int				i;

    //data.game = game;
    game->window = mlx_new_window(game->mlx, S_W,
            S_H, "Cube3D");
    game->drawing_data.img = mlx_new_image(game->mlx, S_W, S_H);
    game->drawing_data.addr = mlx_get_data_addr(game->drawing_data.img, &game->drawing_data.bits_per_pixel,
            &game->drawing_data.line_length, &game->drawing_data.endian);
    i = 0;
    while (i < S_W)
      {
    	ft_draw_vertikal(game, game->lines[i]);
        i++;
      }
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0, 0);
    // data.mlx = game->mlx;
    // data.win = game->window;
    //data.img = game->drawing_data.img;
    //mlx_key_hook(mlx_win, handle_input, &data);
   // mlx_hook(mlx_win, 17, 1L << 17, x_close, &data);
   // mlx_loop(game->mlx);

    //game->window = mlx_new_window(game->mlx, game->columns * MINI_CELL_SIZE, game->rows * MINI_CELL_SIZE, "Cube3D");
	// img.img = mlx_new_image(game->mlx, game.columns * CELL_SIZE, game.rows * CELL_SIZE);
	// //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);

	render_minimap(game);
	printf("(before move) p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	printf("(before move) x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	printf("(before move) angle: %f \n", game->player.p_angle); //debug
	// mlx_put_image_to_window(game->mlx, mlx_win, img.img, 0, 0);

	// mlx_key_hook(game->window, key_pressed, game);
	// mlx_hook(game->window, 17, 1L << 17, x_close, &game);
	// mlx_loop(game->mlx);


	mlx_hook(game->window, 2, 1L << 0, key_press, game);     // KeyPress event
	mlx_hook(game->window, 3, 1L << 1, key_release, game);   // KeyRelease event
	mlx_loop_hook(game->mlx, render_and_update, game);       // Main game loop
	mlx_hook(game->window, 17, 1L << 17, x_close, &game);
	mlx_loop(game->mlx);
}

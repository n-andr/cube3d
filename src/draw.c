/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:39 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/23 19:42:29 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_texture_coord_def(t_game_info *game, t_line line, int *x, int *y)
{
	int	wall_up_part;

	wall_up_part = line.y1 - line.y_top;
	if (line.high)
		*y = wall_up_part * game->textures.height / line.high;
	if (line.w_wall_side == 1 || line.s_wall_side)
		*x = CELL_SIZE - line.offset_x * game->textures.width / CELL_SIZE;
	else
		*x = line.offset_x * game->textures.width / CELL_SIZE;
}

unsigned int	ft_get_pixel_color(t_game_info *game, t_line line, int x, int y)
{
	int				bytes_per_pixel;
	char			*pixel;
	unsigned int	color;

	bytes_per_pixel = game->textures.bpp / 8;
	if (line.w_wall_side)
		pixel = game->textures.w_data + (y * game->textures.size_line) + (x
				* bytes_per_pixel);
	else if (line.s_wall_side)
		pixel = game->textures.s_data + (y * game->textures.size_line) + (x
				* bytes_per_pixel);
	else if (line.n_wall_side)
		pixel = game->textures.n_data + (y * game->textures.size_line) + (x
				* bytes_per_pixel);
	else if (line.e_wall_side)
		pixel = game->textures.e_data + (y * game->textures.size_line) + (x
				* bytes_per_pixel);
	else
		exit(EXIT_FAILURE);
	color = *(unsigned int *)pixel;
	return (color);
}

void	ft_dot_draw(t_game_info *game, t_line line, unsigned int color)
{
	char	*dst;
	int		x;
	int		y;

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
	return ;
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
				draw_cell(x, y, 0x000000, game);
			else if (game->map[y][x] == '1')
				draw_cell(x, y, 0x696969, game);
			else if (game->map[y][x] == '0')
				draw_cell(x, y, 0xFFFFFF, game);
			else if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
				draw_cell(x, y, 0xFFFFFF, game);
			x++;
		}
		y++;
	}
	draw_player(game, 0x0000FF);
}


int key_press(int key, t_game_info *game)
{
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

void	ft_gun_move(t_game_info *game)
{

	if (game->step < 5)
	{
		game->textures.y_gun = game->textures.y_gun - 5;
		game->step = game->step + 1;
	}
	else if (game->step >= 5 && game->step < 10)
	{
		game->textures.y_gun = game->textures.y_gun + 5;
		game->step = game->step + 1;
	}
	else
		game->step = 0;

}

int render_and_update(t_game_info *game)
{
	int	i;

	if (game->key_state.key_w)
	{
		ft_ceiling_color_change(game);
		ft_gun_move(game);
		move_p(game, KEY_W);
	}
	if (game->key_state.key_s)
	{
		ft_ceiling_color_change(game);
		ft_gun_move(game);
		move_p(game, KEY_S);
	}
	if (game->key_state.key_d)
		move_p(game, KEY_D);
	if (game->key_state.key_a)
		move_p(game, KEY_A);
	if (game->key_state.key_left || game->key_state.mouse_turn == -1)
		turn_left(game);
	if (game->key_state.key_right || game->key_state.mouse_turn == 1)
		turn_right(game);
	ft_memset(game->drawing_data.addr, 0, S_W * S_H * sizeof(int));
	ft_floor_ceiling_colour(game);
	ft_raycasting(game);
	i = 0;
	while (i < S_W)
	{
		ft_draw_vertikal(game, game->lines[i], 0);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window,
		game->drawing_data.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.gun_img,
		game->textures.x_gun, game->textures.y_gun);
	render_minimap(game);
	free(game->lines);
	return (0);
}

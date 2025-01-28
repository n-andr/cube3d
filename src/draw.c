/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:39 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/28 02:48:41 by nandreev         ###   ########.fr       */
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

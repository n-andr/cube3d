/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:50:18 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/24 19:51:28 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player(t_game_info *game, int color)
{
	int		i;
	int		j;
	int		start_x;
	int		start_y;
	char	*dst;

	start_x = (game->player.x / (CELL_SIZE / MINI_CELL_SIZE))
		- (MINI_PLAYER_SIZE / 2);
	start_y = (game->player.y / (CELL_SIZE / MINI_CELL_SIZE))
		- (MINI_PLAYER_SIZE / 2);
	i = 0;
	while (i < MINI_PLAYER_SIZE)
	{
		j = 0;
		while (j < MINI_PLAYER_SIZE)
		{
			dst = game->drawing_data.addr
				+ ((start_y + i) * game->drawing_data.line_length
					+ (start_x + j) * (game->drawing_data.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	draw_cell(int x, int y, int color, t_game_info *game)
{
	int		i;
	int		j;
	int		start_x;
	int		start_y;
	char	*dst;

	start_x = x * MINI_CELL_SIZE;
	start_y = y * MINI_CELL_SIZE;
	i = 0;
	while (i < MINI_CELL_SIZE)
	{
		j = 0;
		while (j < MINI_CELL_SIZE)
		{
			dst = game->drawing_data.addr
				+ ((start_y + i) * game->drawing_data.line_length
					+ (start_x + j) * (game->drawing_data.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
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

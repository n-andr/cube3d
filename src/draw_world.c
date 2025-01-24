/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:32:16 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/24 19:50:01 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_floor_ceiling_colour(t_game_info *game)
{
	int				i;
	t_line			line;
	unsigned int	color;

	i = 0;
	color = 0;
	ft_line_def(&line);

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

void	ft_ceiling_color_change(t_game_info *game)
{
	game->textures.ceiling = game->textures.ceiling + 10000;
}

void	ft_game_draw(t_game_info *game)
{
	int	i;

	ft_floor_ceiling_colour(game);
	i = 0;
	while (i < S_W)
	{
		ft_draw_vertikal(game, game->lines[i], 0);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->drawing_data.img, 0,
		0);
	render_minimap(game);
	free(game->lines);
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_hook(game->window, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, render_and_update, game);
	mlx_hook(game->window, 17, 1L << 17, x_close, &game);
	mlx_loop(game->mlx);
}

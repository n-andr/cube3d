/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 02:41:39 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/28 02:50:53 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	move_p(t_game_info *game, int key)
{
	int	row;
	int	col;

	row = game->player.p_position_row;
	col = game->player.p_position_col;
	if (key == KEY_W)
	{
		move_forward(game, row, col);
	}
	else if (key == KEY_S)
	{
		move_back(game, row, col);
	}
	else if (key == KEY_D)
	{
		move_right(game, row, col);
	}
	else if (key == KEY_A)
	{
		move_left(game, row, col);
	}
}

int	key_press(int key, t_game_info *game)
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

void	key_state_check(t_game_info *game)
{
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
}

int	render_and_update(t_game_info *game)
{
	int	i;

	key_state_check(game);
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

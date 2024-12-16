/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:44:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/16 23:02:49 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	turn_left(t_game_info *game)
{
	printf("turn left\n");
	game->player.p_angle -= TURN_ANGLE;

	if (game->player.p_angle < 0)
		game->player.p_angle += 2 * M_PI;
	//game->player.p_angle -= 0.1;
}

void	turn_right(t_game_info *game)
{
	printf("turn right\n");
	game->player.p_angle += TURN_ANGLE;

	if (game->player.p_angle >= 2 * M_PI)
		game->player.p_angle -= 2 * M_PI;
}

void	turn_p(t_game_info *game, int key)
{
	if (key == 65361)
	{
		turn_left(game);
	}
	else if (key == 65363)
	{
		turn_right(game);
	}
	printf("(after) p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	printf("(after) x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	printf("(after) angle: %f \n", game->player.p_angle); //debug
}
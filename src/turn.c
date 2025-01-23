/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:44:12 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 19:21:11 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


// rotate on button press

// key == 65361 - left arrow
// key == 65363 - right arrow

// one turn is TURN_ANGLE
// currently (2 * M_PI / 24) = 15 degrees

// to make a full circle player need 24 turns
// there are some issues with the angle calculation presicion

void	turn_left(t_game_info *game)
{
	game->player.p_angle -= TURN_ANGLE;

	if (game->player.p_angle < 0)
		game->player.p_angle += 2 * M_PI;
}

void	turn_right(t_game_info *game)
{
	game->player.p_angle += TURN_ANGLE;

	if (game->player.p_angle >= 2 * M_PI)
		game->player.p_angle -= 2 * M_PI;
}

void	turn_p(t_game_info *game, int key)
{
	if (key == KEY_LEFT)
	{
		turn_left(game);
	}
	else if (key == KEY_RIGHT)
	{
		turn_right(game);
	}
}

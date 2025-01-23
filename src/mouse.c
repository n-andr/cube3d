/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:28:05 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/20 19:25:10 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


/*
** mouse_move - function to handle mouse movement
** key_state.mouse_turn = -1 left, 1 right, 0 none

x and  y are the current mouse position

if x < third of the screen width then turn left
if x > 2 thirds of the screen width then turn right
else do nothing

*/
int	mouse_move(int x, int y, t_game_info *game)
{
	int	window_width;
	int	third_width;

	window_width = S_W;
	third_width = window_width / 3;
	if (x < 0 || y <  0)
	{
		game->key_state.mouse_turn = 0;
		return (0);
	}
	if (x < third_width)
	{
		game->key_state.mouse_turn = -1;
	}
	else if (x > 2 * third_width)
	{
		game->key_state.mouse_turn = 1;
	}
	else
	{
		game->key_state.mouse_turn = 0;
	}
	return (0);
}

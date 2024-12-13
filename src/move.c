/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:28:05 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/13 01:02:14 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


// move on button press
// rotate on button press
// check if the new position is valid
// if valid update the player position coordinates and the map
// if not valid do nothing


/*The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through the maze.
*/

/*
key == 119 - W
key == 115  - S
key == 100 - D
key == 97 - A

based on ASCII lowercase
*/

void	move_up(t_game_info *game, int row, int col)
{
	if (game->map[row - 1][col] == '0')
	{
		game->map[row][col] = '0';
		game->map[row - 1][col] = 'N'; //do i need to update the player position on the map?
	}
	else if (game->map[row - 1][col] == '1')
		return ;
}

void	move_down(t_game_info *game, int row, int col)
{
	if (game->map[row + 1][col] == '0')
	{
		game->map[row][col] = '0';
		game->map[row + 1][col] = 'N'; //do i need to update the player position on the map?
	}
	else if (game->map[row + 1][col] == '1')
		return ;
}

void	move_left(t_game_info *game, int row, int col)
{
	if (game->map[row][col - 1] == '0')
	{
		game->map[row][col] = '0';
		game->map[row][col - 1] = 'N'; //do i need to update the player position on the map?
	}
	else if (game->map[row][col - 1] == '1')
		return ;
}

void	move_right(t_game_info *game, int row, int col)
{
	if (game->map[row][col + 1] == '0')
	{
		game->map[row][col] = '0';
		game->map[row][col + 1] = 'N'; //do i need to update the player position on the map?
	
	}
	else if (game->map[row][col + 1] == '1')
		return ;
}

void	move_p(t_game_info *game, int key)
{
	// find_p(game, game->map);
	printf("p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col);
	printf("x: %d, y: %d \n", game->player.x,  game->player.y);
	printf("angle: %f \n", game->player.p_angle);
	if (key == 119)
	{
		move_up(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == 115)
	{
		move_down(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == 100)
	{
		move_right(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == 97)
	{
		move_left(game, game->player.p_position_row, game->player.p_position_col);
	}
	render_map(game); // update visuals and minimap

}



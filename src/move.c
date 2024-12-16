/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:28:05 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/16 01:39:22 by nandreev         ###   ########.fr       */
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

void	move_up(t_game_info *game, int p_row, int p_col)
{
	int	new_y;
	int	new_row;

	new_y = game->player.y - STEP_SIZE;
	new_row = new_y / CELL_SIZE;
	if (new_row < p_row && game->map[new_row][p_col] == '0')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][p_col] = 'N'; //do i need to update the player position on the map?
		game->player.p_position_row = new_row;
	}
	else if (game->map[new_row][p_col] != '1')
		game->player.y = new_y;
}

void	move_down(t_game_info *game, int p_row, int p_col)
{
	int	new_y;
	int	new_row;

	new_y = game->player.y + STEP_SIZE;
	new_row = new_y / CELL_SIZE;
	if (new_row > p_row && game->map[new_row][p_col] == '0')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][p_col] = 'N'; //do i need to update the player position on the map?
		game->player.p_position_row = new_row;
	}
	else if (game->map[new_row][p_col] != '1')
		game->player.y = new_y;
}

void	move_left(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_col;

	new_x = game->player.x - STEP_SIZE;
	new_col = new_x / CELL_SIZE;
	if (new_col < p_col && game->map[p_row][new_col] == '0')
	{
		game->map[p_row][p_col] = '0';
		game->map[p_row][new_col] = 'N'; //do i need to update the player position on the map?
		game->player.p_position_col = new_col;
	}
	else if (game->map[p_row][new_col] != '1')
		game->player.x = new_x;
}

void	move_right(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_col;

	new_x = game->player.x + STEP_SIZE;
	new_col = new_x / CELL_SIZE;
	if (new_col > p_col && game->map[p_row][new_col] == '0')
	{
		game->map[p_row][p_col] = '0';
		game->map[p_row][new_col] = 'N'; //do i need to update the player position on the map?
		game->player.p_position_col = new_col;
	}
	else if (game->map[p_row][new_col] != '1')
		game->player.x = new_x;
}

void	move_p(t_game_info *game, int key)
{
	// find_p(game, game->map);
	
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
	printf("(after) p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	printf("(after) x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	printf("(after) angle: %f \n", game->player.p_angle); //debug
	render_map(game); // update visuals and minimap

}



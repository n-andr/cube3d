/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:28:05 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/19 19:09:11 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


// move on button press
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

void	move_forward(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_y;
	int	new_col;
	int	new_row;

	new_x = game->player.x + round(cos(game->player.p_angle) * STEP_SIZE);
	new_y = game->player.y + round(sin(game->player.p_angle) * STEP_SIZE);
	new_row = (new_y - 1) / CELL_SIZE;
	new_col = new_x / CELL_SIZE;
	//draw_player(game, 0x000000); // clear player from minimap
	if (game->map[new_row][new_col] != '1')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][new_col] = 'N'; // Optional: update the map with player's direction
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.p_position_row = new_row;
		game->player.p_position_col = new_col;
	}
}

void	move_back(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_y;
	int	new_col;
	int	new_row;

	new_x = game->player.x - round(cos(game->player.p_angle) * STEP_SIZE);
	new_y = game->player.y - round(sin(game->player.p_angle) * STEP_SIZE);
	new_row = new_y / CELL_SIZE;
	new_col = new_x / CELL_SIZE;
	//draw_player(game, 0x000000); // clear player from minimap
	if (game->map[new_row][new_col] != '1')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][new_col] = 'N'; // Optional: update the map with player's direction
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.p_position_row = new_row;
		game->player.p_position_col = new_col;
	}
}

void	move_left(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_y;
	int	new_col;
	int	new_row;

	new_x = game->player.x + round(sin(game->player.p_angle) * STEP_SIZE);
	new_y = game->player.y - round(cos(game->player.p_angle) * STEP_SIZE);
	new_row = new_y / CELL_SIZE;
	new_col = (new_x - 1) / CELL_SIZE;
	//draw_player(game, 0x000000); // clear player from minimap
	if (game->map[new_row][new_col] != '1')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][new_col] = 'N'; // Optional: update the map with player's direction
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.p_position_row = new_row;
		game->player.p_position_col = new_col;
	}
}

void	move_right(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_y;
	int	new_col;
	int	new_row;

	new_x = game->player.x - round(sin(game->player.p_angle) * STEP_SIZE);
	new_y = game->player.y + round(cos(game->player.p_angle) * STEP_SIZE);
	new_row = new_y / CELL_SIZE;
	new_col = new_x / CELL_SIZE;
	//draw_player(game, 0x000000); // clear player from minimap
	if (game->map[new_row][new_col] != '1')
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][new_col] = 'N'; // Optional: update the map with player's direction
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.p_position_row = new_row;
		game->player.p_position_col = new_col;
	}
}

void	move_p(t_game_info *game, int key) // not used?
{
	// find_p(game, game->map);

	if (key == KEY_W)
	{
		move_forward(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == KEY_S)
	{
		move_back(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == KEY_D)
	{
		move_right(game, game->player.p_position_row, game->player.p_position_col);
	}
	else if (key == KEY_A)
	{
		move_left(game, game->player.p_position_row, game->player.p_position_col);
	}
	//printf("p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	//printf("x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	//printf("angle: %f \n", game->player.p_angle); //debug

}

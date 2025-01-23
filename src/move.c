/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:28:05 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 19:24:54 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


// move on button press
// check if the new position is valid
// if valid update the player position coordinates and the map
// if not valid do nothing


/*
The left and right
arrow keys of the keyboard
must allow you to lookleft and right in the maze.
The W, A, S, and D keys must allow you to move the point of view through the maze.
*/


/*
key == 119 - W
key == 115  - S
key == 100 - D
key == 97 - A

based on ASCII lowercase
*/


// collision detection
// check if the new position is valid
// column = x / CELL_SIZE
// row = y / CELL_SIZE

// check if every corner of the player is in a valid position
bool	is_valid_move(t_game_info *game, int new_x, int new_y)
{
	int	new_col;
	int	new_row;

	new_col = (new_x - (PLAYER_SIZE / 2)) / CELL_SIZE;
	new_row = (new_y - (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (new_row < 0 || new_row >= game->rows || new_col < 0
		|| new_col >= game->columns || game->map[new_row][new_col] == '1')
		return (false);
	new_col = (new_x + (PLAYER_SIZE / 2)) / CELL_SIZE;
	new_row = (new_y - (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (new_row < 0 || new_row >= game->rows || new_col < 0
		|| new_col >= game->columns || game->map[new_row][new_col] == '1')
		return (false);
	new_col = (new_x + (PLAYER_SIZE / 2)) / CELL_SIZE;
	new_row = (new_y + (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (new_row < 0 || new_row >= game->rows || new_col < 0
		|| new_col >= game->columns || game->map[new_row][new_col] == '1')
		return (false);
	new_col = (new_x - (PLAYER_SIZE / 2)) / CELL_SIZE;
	new_row = (new_y + (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (new_row < 0 || new_row >= game->rows || new_col < 0
		|| new_col >= game->columns || game->map[new_row][new_col] == '1')
		return (false);
	return (true);
}

void	move_forward(t_game_info *game, int p_row, int p_col)
{
	int	new_x;
	int	new_y;
	int	new_col;
	int	new_row;

	new_x = game->player.x + round(cos(game->player.p_angle) * STEP_SIZE);
	new_y = game->player.y + round(sin(game->player.p_angle) * STEP_SIZE);

	new_row = new_y / CELL_SIZE;
	new_col = new_x / CELL_SIZE;
	// Determine the grid cells the player would occupy with the new position
	// new_row = (new_y - (PLAYER_SIZE / 2)) / CELL_SIZE;
	// new_col = (new_x - (PLAYER_SIZE / 2)) / CELL_SIZE;

	// Check if the new position is valid
	if (is_valid_move(game, new_x, new_y))
	{
		// Update the map and player position
		game->map[p_row][p_col] = '0'; // Clear the old position
		game->map[new_row][new_col] = 'N'; // Optional: update map with player's direction
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
	// new_row = (new_y - (PLAYER_SIZE / 2)) / CELL_SIZE;
	// new_col = (new_x - (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (is_valid_move(game, new_x, new_y))
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
	// new_row = new_y / CELL_SIZE;
	// new_col = (new_x - 1) / CELL_SIZE;
	new_row = new_y / CELL_SIZE;
	new_col = new_x / CELL_SIZE;
	// new_row = (new_y - (PLAYER_SIZE / 2)) / CELL_SIZE;
	// new_col = (new_x - (PLAYER_SIZE / 2)) / CELL_SIZE;
	if (is_valid_move(game, new_x, new_y))
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
	if (is_valid_move(game, new_x, new_y))
	{
		game->map[p_row][p_col] = '0';
		game->map[new_row][new_col] = 'N'; // Optional: update the map with player's direction
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.p_position_row = new_row;
		game->player.p_position_col = new_col;
	}
	// printf("p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
	// printf("x: %d, y: %d \n", game->player.x,  game->player.y); //debug
	// printf("angle: %f \n", game->player.p_angle); //debug
}


void	move_p(t_game_info *game, int key) // not used?
{

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
}

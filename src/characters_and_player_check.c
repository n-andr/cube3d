/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters_and_player_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/28 17:23:38 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Check map contetn to consider map valid

p_check - returnes the number of N,S,E or W for the player’s start position found in the map (must be 1)
c_chrck - returnes the numberof C found in the map (must be 1 or more)
e_check - returnes the numberof E found in the map (must be 1)
characters_check - checks if there are only C 0 P E 1 characters,
if no exits the program
elements_check - checks if P C E are a valid number
*/
#include "../cube3d.h"

int	p_check(t_game_info *game)
{
	int	row;
	int	col;
	int	p_count;

	row = 0;
	col = 0;
	p_count = 0;
	while (row < game->rows)
	{
		while (col < game->columns)
		{
			if ((game->map[row][col] == 'N') || (game->map[row][col] == 'S')
				|| (game->map[row][col] == 'E') || (game->map[row][col] == 'W'))
			{
				p_count ++;
				game->p_position_row = row;
				game->p_position_col = col;
				if (game->map[row][col] == 'N')
				game->p_angle = (3 * M_PI)/2;
				else if (game->map[row][col] == 'S')
				game->p_angle = M_PI/2;
				else if (game->map[row][col] == 'E')
				game->p_angle = 0;
				else if (game->map[row][col] == 'W')
				game->p_angle = M_PI;
			}
			col++;
		}
		col = 0;
		row ++;
	}
    // game->first_ray_angle = game->p_angle - M_PI/6;
    // game->p_cell_x = CELL_SIZE * game->p_position_col + CELL_SIZE / 2;
    // game->p_cell_y = CELL_SIZE * game->p_position_row + CELL_SIZE / 2;
	// game->delt_angle = M_PI / (3 * S_W);
	return (p_count);
}


void	player_position_check(t_game_info *game)
{
	if (p_check(game) != 1)
	{
		write(1, "Error\nThe map must contain 1 player starting position\n", 54);
		free_array(game->map);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	characters_check(t_game_info *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (col < game->columns)
		{
			if (game->map[row][col] != 'N'
				&& game->map[row][col] != 'E'
				&& game->map[row][col] != 'S'
				&& game->map[row][col] != 'W'
				&& game->map[row][col] != '1'
				&& game->map[row][col] != ' '
				&& game->map[row][col] != '0')
			{
				write(1, "Error\nForbiden character\n", 25);
				//debug
				printf("row = %d, col = %d, char = %c\n", row, col, game->map[row][col]);
				free_array(game->map);
				exit(EXIT_FAILURE);
			}
			col++;
		}
		row++;
	}
}

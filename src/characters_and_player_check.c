/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters_and_player_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/28 03:11:51 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Check map content to consider map valid

p_check - returnes the number of N,S,E or W 
for the player’s start position found in the map (must be 1)
characters_check - checks if there are only 0, ,1,N,S,E or W characters,
if no exits the program
*/

#include "../cube3d.h"

static void	save_player_position(t_game_info *game, int row, int col)
{
	game->player.p_position_row = row;
	game->player.p_position_col = col;
	if (game->map[row][col] == 'N')
		game->player.p_angle = (3 * M_PI) / 2;
	else if (game->map[row][col] == 'S')
		game->player.p_angle = M_PI / 2;
	else if (game->map[row][col] == 'E')
		game->player.p_angle = 2 * M_PI;
	else if (game->map[row][col] == 'W')
		game->player.p_angle = M_PI;
}

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
				save_player_position(game, row, col);
			}
			col++;
		}
		col = 0;
		row ++;
	}
	game->player.x = CELL_SIZE * game->player.p_position_col + CELL_SIZE / 2;
	game->player.y = CELL_SIZE * game->player.p_position_row + CELL_SIZE / 2;
	return (p_count);
}

void	player_position_check(t_game_info *game)
{
	if (p_check(game) != 1)
	{
		write(1, "Error\nThe map must contain "
			"1 player starting position\n", 54);
		close_game(game, EXIT_FAILURE);
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
		while (game->map[row][col] != '\0')
		{
			if (game->map[row][col] != 'N'
				&& game->map[row][col] != 'E'
				&& game->map[row][col] != 'S'
				&& game->map[row][col] != 'W'
				&& game->map[row][col] != '1'
				&& game->map[row][col] != ' '
				&& game->map[row][col] != '0')
			{
				write(1, "Error\nForbiden character in the map "
					"or textures are after the map\n", 66);
				close_game(game, EXIT_FAILURE);
			}
			col++;
		}
		row++;
	}
}

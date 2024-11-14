/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/14 15:45:23 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Check map contetn to consider map valid

p_check - returnes the numberof P found in the map (must be 1)
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
			if (game->map[row][col] == 'P')
				p_count ++;
			col++;
		}
		col = 0;
		row++;
	}
	return (p_count);
}

int	e_check(t_game_info *game)
{
	int	row;
	int	col;
	int	e_count;

	row = 0;
	col = 0;
	e_count = 0;
	while (row < game->rows)
	{
		while (col < game->columns)
		{
			if (game->map[row][col] == 'E')
				e_count ++;
			col++;
		}
		col = 0;
		row++;
	}
	game->exit_check = 0;
	return (e_count);
}

int	c_check(t_game_info *game)
{
	int	row;
	int	col;

	row = 0;
	game->c_count = 0;
	while (row < game->rows)
	{
		col = 0;
		while (col < game->columns)
		{
			if (game->map[row][col] == 'C')
				game->c_count ++;
			col++;
		}
		row++;
	}
	game->collectibles = game->c_count;
	game->c_count = 0;
	return (game->collectibles);
}

void	elements_check(t_game_info *game)
{
	if (p_check(game) != 1)
	{
		write(1, "Error\nThe map must contain 1 P\n", 31);
		free_map(game);
		exit(EXIT_FAILURE);
	}
	if (e_check(game) != 1)
	{
		write(1, "Error\nThe map must contain 1 E\n", 31);
		free_map(game);
		exit(EXIT_FAILURE);
	}
	if (c_check(game) < 1)
	{
		write(1, "Error\nThe map must contain min 1 C\n", 36);
		free_map(game);
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
			if (game->map[row][col] != 'C'
				&& game->map[row][col] != '1'
				&& game->map[row][col] != '0'
				&& game->map[row][col] != 'E'
				&& game->map[row][col] != 'P')
			{
				write(1, "Error\nForbiden character\n", 25);
				free_map(game);
				exit(EXIT_FAILURE);
			}
			col++;
		}
		row++;
	}
}

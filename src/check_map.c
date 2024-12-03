/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/03 16:41:26 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


/**
 * check_eight_neighbours - Validates the neighbors of a cell in a 2D map.
 *
 * @map: A pointer to the 2D character array representing the map.
 * @i: The row index of the cell being checked.
 * @j: The column index of the cell being checked.
 *
 * Description:
 * This function checks if a specific cell at position (i, j) in a 2D map is 
 * surrounded by any invalid neighbors ('0'). It handles boundary conditions:
 * - If the cell is in the first row (i == 0), it checks relevant neighbors below
 *   and to the sides.
 * - If the cell is in the last row (map[i + 1] == NULL), it checks neighbors 
 *   above and to the sides.
 * - For cells not on the boundary, it checks all 8 surrounding neighbors 
 *   (above, below, left, right, and diagonals).
 *
 * Return:
 * - false: If any neighbor is invalid ('0').
 * - true: If all neighbors are valid.
 */

bool	check_eight_neighbours(char **map, int i, int j)
{
	if (i == 0)
	{
		if (j != 0)
		{
			if (map[i + 1][j - 1]  == '0'
				|| map[i][j - 1]  == '0')	
				return (false);
		}
		if (map[i + 1][j]  == '0'
			|| map[i + 1][j + 1]  == '0'
			|| map[i][j + 1]  == '0')
			return (false);
	}
	else if (map[i + 1] == NULL)
	{
		if (j != 0)
		{
			if (map[i - 1][j - 1]  == '0'
				|| map[i][j - 1]  == '0')
				return (false);
		}
		if (map[i - 1][j]  == '0'
			|| map[i - 1][j + 1]  == '0'
			|| map[i][j + 1]  == '0')
			return (false);
	}
	else 
	{
		if (j != 0)
		{
			if(map[i - 1][j - 1]  == '0'
				|| map[i + 1][j - 1]  == '0'
				|| map[i][j - 1]  == '0')
				return (false);
		}
		if (map[i - 1][j]  == '0'
			|| map[i - 1][j + 1]  == '0'
			|| map[i + 1][j]  == '0'
			|| map[i + 1][j + 1]  == '0'
			|| map[i][j + 1]  == '0')
			return (false);
	}
	return (true);
}




// checking the border of any shape
// bool	check_eight_neighbours(char **map,int i, int j)
// {
// 	if (i == 0 && j == 0 )
// 	{
// 		if (map[i + 1][j]  == '0'
// 			|| map[i + 1][j + 1]  == '0'
// 			|| map[i][j + 1]  == '0')
// 			return (false);
// 	}
// 	else if (i == 0)
// 	{
// 		if (map[i + 1][j]  == '0'
// 			|| map[i + 1][j - 1]  == '0'
// 			|| map[i + 1][j + 1]  == '0'
// 			|| map[i][j - 1]  == '0'
// 			|| map[i][j + 1]  == '0')	
// 			return (false);
// 	}
// 	else if (map[i + 1] == NULL && j == 0)
// 	{
// 		if (map[i - 1][j]  == '0'
// 			|| map[i - 1][j + 1]  == '0'
// 			|| map[i][j + 1]  == '0')
// 			return (false);
// 	}
// 	else if (map[i + 1] == NULL)
// 	{
// 		if (map[i - 1][j]  == '0'
// 			|| map[i - 1][j - 1]  == '0'
// 			|| map[i - 1][j + 1]  == '0'
// 			|| map[i][j - 1]  == '0'
// 			|| map[i][j + 1]  == '0')
// 			return (false);
// 	}
// 	else 
// 	{
// 		if (map[i - 1][j]  == '0'
// 			|| map[i - 1][j - 1]  == '0'
// 			|| map[i - 1][j + 1]  == '0'
// 			|| map[i + 1][j]  == '0'
// 			|| map[i + 1][j - 1]  == '0'
// 			|| map[i + 1][j + 1]  == '0'
// 			|| map[i][j - 1]  == '0'
// 			|| map[i][j + 1]  == '0')
// 			return (false);
// 	}
// 	return (true);
// }


bool	first_last_row_col(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] == '0')
			return (false);
		j++;
	}
	while (map[i])
	{
		if (map[i][0] == '0' || map[i][ft_strlen(map[i]) - 2] == '0')
			return (false);
		i++;
	}
	j = 0;
	while (map[i - 1][j])
	{
		if (map[i - 1][j] == '0')
			return (false);
		j++;
	}
	return (true);
}
bool	is_closed(t_game_info *game)
{
	int i;
	int j;
	char **map;

	i = 0;
	map = malloc(sizeof(char *) * (game->rows + 1));
	if (map == NULL)
		return (false); // do malloc error handling
	while (i < game->rows)
	{
		map[i] = ft_calloc(game->columns + 1, sizeof(char)); // use calloc instead of malloc
		if (map[i] == NULL)
			return (false); // do malloc error handling
		ft_strlcpy(map[i], game->map[i], (ft_strlen(game->map[i]) + 1));
		i ++;
	}
	map[i] = NULL;
	i = 0;
	map[game->p_position_row][game->p_position_col] = '0';

	if (first_last_row_col(map) == false)
	{
		free_array(map);
		return (false);
	}
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && check_eight_neighbours(map, i, j) == false)
			{
				free_array(map);
				return (false);
			}
			j++;
		}
		i++;
	}
	free_array(map);
	return (true);
	
}

void	check_map(t_game_info *game)
{
	//is_rectangular(game);

	// do we need to check the size of the map?
	// can we handle any size?


	
	player_position_check(game);
	characters_check(game);
	if (map_is_one_piece(game) == false)
	{
		write(1, "Error\nMap is fragmented\n", 24);
		close_game(game);
		exit(EXIT_FAILURE);
	}
	if (is_closed(game) == false)
	{
		write(1, "Error\nMap is not closed\n", 24);
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_perimeter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 02:25:48 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/28 02:32:27 by nandreev         ###   ########.fr       */
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

bool	other_neighbours(char **map, int i, int j)
{
	if (j != 0)
	{
		if (map[i - 1][j - 1] == '0'
			|| map[i + 1][j - 1] == '0'
			|| map[i][j - 1] == '0')
			return (false);
	}
	if (map[i - 1][j] == '0'
		|| map[i - 1][j + 1] == '0'
		|| map[i + 1][j] == '0'
		|| map[i + 1][j + 1] == '0'
		|| map[i][j + 1] == '0')
		return (false);
	return (true);
}

bool	check_eight_neighbours(char **map, int i, int j)
{
	if (i == 0)
	{
		if (j != 0)
		{
			if (map[i + 1][j - 1] == '0' || map[i][j - 1] == '0')
				return (false);
		}
		if (map[i + 1][j] == '0' || map[i + 1][j + 1] == '0'
			|| map[i][j + 1] == '0')
			return (false);
	}
	else if (map[i + 1] == NULL)
	{
		if (j != 0)
		{
			if (map[i - 1][j - 1] == '0' || map[i][j - 1] == '0')
				return (false);
		}
		if (map[i - 1][j] == '0' || map[i - 1][j + 1] == '0'
			|| map[i][j + 1] == '0')
			return (false);
	}
	else
		return (other_neighbours(map, i, j));
	return (true);
}

bool	first_last_row_col(char **map)
{
	int	i;
	int	j;

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

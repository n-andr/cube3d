/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:57:07 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/14 15:45:14 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	flood_fill(char **map, int row, int col, t_game_info *game)
{
	if (game->exit_check == 1 && game->c_count == game->collectibles)
		return (1);
	else if (map[row][col] == 'E')
	{
		game->exit_check = 1;
		return (0);
	}
	else if (map[row][col] == '0' || map[row][col] == 'C'
		|| map[row][col] == 'P')
	{
		if (map[row][col] == 'C')
			game->c_count ++;
		map[row][col] = '+';
		if (flood_fill(map, row + 1, col, game) == 1
			|| flood_fill(map, row - 1, col, game) == 1
			|| flood_fill(map, row, col + 1, game) == 1
			|| flood_fill(map, row, col - 1, game) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	find_p(t_game_info *game, char **map)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (col < game->columns)
		{
			if (map[row][col] == 'P')
			{
				game->p_position_row = row;
				game->p_position_col = col;
				return ;
			}
			col++;
		}
		row++;
	}
}

int	has_valid_path(t_game_info *game)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (game->rows + 1));
	if (map == NULL)
		return (0);
	while (i < game->rows)
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(game->map[i]) + 1));
		if (map[i] == NULL)
			return (0);
		ft_strlcpy(map[i], game->map[i], ft_strlen(game->map[i]) + 1);
		i ++;
	}
	map[i] = NULL;
	find_p(game, map);
	if (flood_fill(map, game->p_position_row, game->p_position_col, game) == 1)
	{
		free_check_map(map);
		game->c_count = 0;
		return (1);
	}
	free_check_map(map);
	return (0);
}

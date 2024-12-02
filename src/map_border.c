/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:57:07 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/02 03:22:51 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	flood_fill(char **map, int row, int col, t_game_info *game)
{
	if (row < 0 || col < 0 || row >= game->rows || col >= ft_strlen(map[row]))
    	return;
	if (map[row][col] == '0' || map[row][col] == '1' || map[row][col] == 'N' 
		|| map[row][col] == 'S' || map[row][col] == 'W' || map[row][col] == 'E')
	{
		map[row][col] = '+';
		flood_fill(map, row + 1, col, game);
		flood_fill(map, row - 1, col, game);
		flood_fill(map, row, col + 1, game);
		flood_fill(map, row, col - 1, game);
	}
}

bool	one_fragment(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '+' && map[i][j] != '\0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	map_is_one_piece(t_game_info *game)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (game->rows + 1));
	if (map == NULL)
		return (false); // do malloc error handling
	while (i < game->rows)
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(game->map[i]) + 1));
		if (map[i] == NULL)
			return (false); // do malloc error handling
		ft_strlcpy(map[i], game->map[i], ft_strlen(game->map[i]) + 1);
		i ++;
	}
	map[i] = NULL;
	flood_fill(map, game->p_position_row, game->p_position_col, game);
	if ( one_fragment(map) == false)
	{
		free_array(map);
		return (false);
	}
	free_array(map);
	return (true);
}

bool	check_eight_neighbours(char **map,int i, int j)
{
	if (map[i - 1][j] == '0' 
		|| map[i - 1][j - 1]  == '0'
		|| map[i - 1][j + 1]  == '0'
		|| map[i + 1][j]  == '0'
		|| map[i + 1][j - 1]  == '0'
		|| map[i + 1][j + 1]  == '0'
		|| map[i][j - 1]  == '0'
		|| map[i][j + 1]  == '0')
		return (false);
	return (true);

}
bool	first_last_row_col(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '0' || map[i][ft_strlen(map[i])] == '0')
			return (false);
		i++;
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

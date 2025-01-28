/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/28 03:10:06 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	perimeter(char **map)
{
	int	i;
	int	j;

	i = 0;
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
	return (true);
}

bool	is_closed(t_game_info *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (game->rows + 1));
	if (map == NULL)
		return (false);
	while (i < game->rows)
	{
		map[i] = ft_calloc(game->columns + 1, sizeof(char));
		if (map[i] == NULL)
			return (false);
		ft_strlcpy(map[i], game->map[i], (ft_strlen(game->map[i]) + 1));
		i ++;
	}
	map[i] = NULL;
	map[game->player.p_position_row][game->player.p_position_col] = '0';
	if (perimeter(map) == false)
		return (false);
	free_array(map);
	return (true);
}

void	check_map(t_game_info *game)
{
	characters_check(game);
	player_position_check(game);
	if (map_is_one_piece(game) == false)
	{
		write(1, "Error\nMap is fragmented\n", 24);
		close_game(game, EXIT_FAILURE);
	}
	if (is_closed(game) == false)
	{
		write(1, "Error\nMap is not closed\n", 24);
		close_game(game, EXIT_FAILURE);
	}
}

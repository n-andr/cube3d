/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2024/12/02 03:01:36 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// change to checkingthe border of any shape

void	is_rectangular(t_game_info *game)
{
	int	i;

	i = 1;
	if (game->map[0] == NULL)
	{
		write(1, "Error\nEmpty map\n", 16);
		free_array(game->map);
		exit(EXIT_FAILURE);
	}
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) == ft_strlen(game->map[i - 1]))
		{
			i++;
		}
		else
		{
			write(1, "Error\nMap is not rectangular\n", 29);
			free_array(game->map);
			exit(EXIT_FAILURE);
		}
		game->columns = ft_strlen(game->map[0]);
	}
}

int	check_first_last_row(char *row)
{
	int	k;

	k = 0;
	while (row[k] != '\0')
	{
		if (row[k] != '1')
			return (0);
		k++;
	}
	return (1);
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

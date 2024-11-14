/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/14 15:45:18 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	is_rectangular(t_game_info *game)
{
	int	i;

	i = 1;
	if (game->map[0] == NULL)
	{
		write(1, "Error\nEmpty map\n", 16);
		free_map(game);
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
			free_map(game);
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

int	is_closed(t_game_info *game)
{
	int	i;

	if (!check_first_last_row(game->map[0])
		|| !check_first_last_row(game->map[game->rows - 1]))
		return (0);
	i = 1;
	while (i < game->rows - 1)
	{
		if (game->map[i][0] != '1' ||
			game->map[i][game->columns - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	check_map(t_game_info *game)
{
	is_rectangular(game);
	if (game->rows > 25 || game->columns > 45)
	{
		write(1, "Error\nMap is too big\n", 21);
		free_map(game);
		exit(EXIT_FAILURE);
	}
	if (is_closed(game) != 1)
	{
		write(1, "Error\nMap is not closed\n", 24);
		free_map(game);
		exit(EXIT_FAILURE);
	}
	elements_check(game);
	characters_check(game);
	if (has_valid_path(game) != 1)
	{
		write(1, "Error\nNo valid path\n", 21);
		free_map(game);
		exit(EXIT_FAILURE);
	}
}

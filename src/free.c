/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/27 16:45:15 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_error(t_game_info *game, int file, char *message, char *str)
{
	write(1, message, ft_strlen(message));
	if (file != -1)
	{
		close(file);
	}
	if (str)
		free(str);
	if (game->map)
	{
		free_map(game);
	}
	//mlx_destroy_window(game->mlx, game->window);
	//free(game->mlx);
	if (game->mlx != NULL)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	exit(EXIT_FAILURE);
}

void	free_map(t_game_info *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free (game->map[i]);
		i ++;
	}
	free (game->map);
}

void	free_check_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free (map[i]);
		i ++;
	}
	free (map);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i ++;
	}
	free (array);
}

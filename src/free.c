/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/28 17:23:12 by nandreev         ###   ########.fr       */
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
		free_array(game->map);
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

// void	free_map(t_game_info *game)
// {
// 	int	i;

// 	i = 0;
// 	while (game->map[i])
// 	{
// 		free (game->map[i]);
// 		i ++;
// 	}
// 	free (game->map);
// }


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

void	free_textures(t_game_info *game)
{
	mlx_destroy_image(game->mlx, game->textures.north);
	mlx_destroy_image(game->mlx, game->textures.south);
	mlx_destroy_image(game->mlx, game->textures.east);
	mlx_destroy_image(game->mlx, game->textures.west);
}

int	close_game(t_game_info *game)
{
	free_array(game->map); //free map array
	free_textures(game); //free images
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
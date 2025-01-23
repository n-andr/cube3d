/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:18:09 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 16:04:18 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_error(t_game_info *game, int file, char *message, char *str)
{
	write(1, message, ft_strlen(message));
	if (str)
		free(str);
	if (file != -1)
	{
		close(file);
	}
	close_game(game, EXIT_FAILURE);
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
	if (array)
	{
		while (array[i])
		{
			free (array[i]);
			i ++;
		}
		free (array);
	}
}

void	free_textures(t_game_info *game)
{
	if (game->textures.north_img)
		mlx_destroy_image(game->mlx, game->textures.north_img);
	if (game->textures.south_img)
		mlx_destroy_image(game->mlx, game->textures.south_img);
	if (game->textures.east_img)
		mlx_destroy_image(game->mlx, game->textures.east_img);
	if (game->textures.west_img)
		mlx_destroy_image(game->mlx, game->textures.west_img);
}

int	close_game(t_game_info *game, int exit_status)
{
	free_array(game->map); //free map array
	if (game->drawing_data.img)
		mlx_destroy_image(game->mlx, game->drawing_data.img);
	free_textures(game); //free images
	if (game->mlx != NULL && game->window != NULL)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx != NULL)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(exit_status);
	return (0);
}

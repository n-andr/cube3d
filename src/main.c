/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/21 17:21:29 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


// a scene description file with the .cub extension
void	is_cub(char *map_adress)
{
	if (map_adress[ft_strlen(map_adress) - 1] == 'b'
		&& map_adress[ft_strlen(map_adress) - 2] == 'u'
		&& map_adress[ft_strlen(map_adress) - 3] == 'c'
		&& map_adress[ft_strlen(map_adress) - 4] == '.')
		return ;
	else
	{
		write(1, "Error\nProgramm accepts only .cub files\n", 39);
		exit(EXIT_FAILURE);
	}
}

void	init_game(t_game_info *game)
{
	game->map = NULL;
	game->rows = 0;
	game->columns = 0;
	game->p_position_row = 0;
	game->p_position_col = 0;
	game->img_width = 500;
	game->img_height = 338;
	game->mlx = mlx_init();
	// game->window = mlx_new_window(game->mlx, 640, 480, "Hello world!");
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	game->textures.floor = NULL;
	game->textures.ceiling = NULL;
}

void	ft_set_values(t_game_info *game)
{
	game->colour = 16777215;
	game->first_ray_angle = game->p_angle - M_PI/6;
	game->p_cell_x = CELL_SIZE * game->p_position_col + CELL_SIZE / 2;
	game->p_cell_y = CELL_SIZE * game->p_position_row + CELL_SIZE / 2;
	game->delt_angle = M_PI / (3 * S_W);
}

int	main(int argc, char **argv)
{
	t_game_info	game;

	if (argc == 2)
	{
		is_cub(argv[1]);
		init_game(&game);
		read_map(argv[1], &game);
	}
	else
	{
		write(1, "Error\nProgramm accepts only 1 argument\n", 39);
		exit(EXIT_FAILURE);
	}
	ft_set_values(&game);
	ft_raycasting(&game);
	ft_game_draw(&game);
	return (0);
}

// mlx_hook - for different events (mouse movements, close the window etc)
// mlx_key_hook - only for keyboard events
//need to handle cntr c to have no leaks???

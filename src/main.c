/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:12 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/10 20:06:31 by mkokorev         ###   ########.fr       */
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
	game->player.p_position_row = 0;
	game->player.p_position_col = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.fov_angle = M_PI / 3;
	game->player.p_angle = 0;
	game->map_width = 500;
	game->map_height = 338;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		printf("Error initializing mlx\n");
		exit(EXIT_FAILURE);
	}
	game->textures.floor = -1;
	game->textures.ceiling = -1;
	game->textures.north_img = NULL;
	game->textures.south_img = NULL;
	game->textures.west_img = NULL;
	game->textures.east_img = NULL;
	game->delt_angle = M_PI / (3 * S_W);
	game->window = mlx_new_window(game->mlx, S_W,
	S_H, "Cube3D");
	game->drawing_data.img = mlx_new_image(game->mlx, S_W, S_H);
	game->drawing_data.addr = mlx_get_data_addr(game->drawing_data.img,
		&game->drawing_data.bits_per_pixel,
			&game->drawing_data.line_length, &game->drawing_data.endian);
}

void test_texture_render(t_game_info *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->textures.north_img, 800, 500);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.west_img, 800, 600);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.south_img, 900, 500);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.east_img, 900, 600);
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
	ft_raycasting(&game);
	ft_game_draw(&game); // Nata
	return (0);
}

// mlx_hook - for different events (mouse movements, close the window etc)
// mlx_key_hook - only for keyboard events
//need to handle cntr c to have no leaks???

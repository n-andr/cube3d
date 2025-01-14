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
	game->map_width = 500;
	game->map_height = 338;
	game->mlx = mlx_init();
	game->window = NULL;
	game->drawing_data.addr = NULL;
	game->drawing_data.img = NULL;
	game->textures.north_img = NULL;
	game->textures.south_img = NULL;
	game->textures.west_img = NULL;
	game->textures.east_img = NULL;
	game->textures.floor = -1;
	game->textures.ceiling = -1;
	game->colour = 16777215;
	game->delt_angle = M_PI / (3 * S_W);
	game->player.fov_angle = M_PI / 3;
	game->epsilon = 0.00001;
}

void test_texture_render(t_game_info *game) {
	//game->window = mlx_new_window(game->mlx, S_W,
	//	S_H, "Cube3D");
	//game->textures.east_img = mlx_new_image(game->mlx, S_W, S_H);
	//game->drawing_data.addr = mlx_get_data_addr(game->drawing_data.img,
	//	&game->drawing_data.bits_per_pixel,
	//		&game->drawing_data.line_length, &game->drawing_data.endian);

	game->window = mlx_new_window(game->mlx, 640, 480, "Hello world!");

	// Draw each texture at different positions for testing
	mlx_put_image_to_window(game->mlx, game->window, game->textures.north_img, 400, 400);  // North texture
	//mlx_put_image_to_window(mlx_ptr, win_ptr, texture->south_img, 200, 0); // South texture
	//mlx_put_image_to_window(mlx_ptr, win_ptr, texture->west_img, 0, 200);  // West texture
	//mlx_put_image_to_window(mlx_ptr, win_ptr, texture->east_img, 200, 200); // East texture
	mlx_loop(game->mlx);
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
	printf("Width: %d, Height: %d\n", game.textures.width, game.textures.height);
	//test_texture_render(&game);
	return (0);
}

// mlx_hook - for different events (mouse movements, close the window etc)
// mlx_key_hook - only for keyboard events
//need to handle cntr c to have no leaks???

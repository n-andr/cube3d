/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:12 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 19:25:55 by mkokorev         ###   ########.fr       */
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

void	ft_init_graphics(t_game_info *game)
{
	game->window = mlx_new_window(game->mlx, S_W, S_H, "Cube3D");
	game->drawing_data.img = mlx_new_image(game->mlx, S_W, S_H);
	game->drawing_data.addr = mlx_get_data_addr(game->drawing_data.img,
			&game->drawing_data.bits_per_pixel, &game->drawing_data.line_length,
			&game->drawing_data.endian);
	game->textures.gun_img = mlx_xpm_file_to_image(game->mlx,
			"./assets/2000p.xpm",
			&game->textures.gun_width, &game->textures.gun_height);
	if (game->textures.gun_img == NULL)
		handle_error(game, 1, "Error\nNo gun texture\n", NULL);
	game->textures.gun_data = mlx_get_data_addr(game->textures.gun_img,
			&game->textures.bpp, &game->textures.size_line,
			&game->textures.endian);
}

void	ft_init_game_2(t_game_info *game)
{
	ft_set_textures_params(game);
	game->key_state.key_w = 0;
	game->key_state.key_s = 0;
	game->key_state.key_a = 0;
	game->key_state.key_d = 0;
	game->key_state.key_left = 0;
	game->key_state.key_right = 0;
	game->key_state.mouse_turn = 0;
	game->delt_angle = M_PI / (3 * S_W);
	game->player.fov_angle = M_PI / 3;
	game->map_width = 500;
	game->map_height = 338;
	game->textures.x_gun = S_W / 2 - game->textures.gun_width / 2;
	game->textures.y_gun = S_H - game->textures.gun_height + 30;
	game->step = 0;
}

void	ft_init_game_1(t_game_info *game)
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
	game->textures.floor = -1;
	game->textures.ceiling = -1;
	game->textures.north_img = NULL;
	game->textures.south_img = NULL;
	game->textures.west_img = NULL;
	game->textures.east_img = NULL;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		printf("Error initializing mlx\n");
		exit(EXIT_FAILURE);
	}
	game->window = NULL;
	game->drawing_data.img = NULL;
}

int	main(int argc, char **argv)
{
	t_game_info	game;

	if (argc == 2)
	{
		is_cub(argv[1]);
		ft_init_game_1(&game);
		read_map(argv[1], &game);
		ft_init_graphics(&game);
		ft_init_game_2(&game);
	}
	else
	{
		write(1, "Error\nProgramm accepts only 1 argument\n", 39);
		exit(EXIT_FAILURE);
	}
	ft_raycasting(&game);
	ft_game_draw(&game);
	return (0);
}

// mlx_hook - for different events (mouse movements, close the window etc)
// mlx_key_hook - only for keyboard events
// need to handle cntr c to have no leaks???

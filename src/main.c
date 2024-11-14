/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/14 16:27:59 by nandreev         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game_info	game;

	if (argc == 2)
	{
		is_cub(argv[1]);
		read_map(argv[1], &game);
	}
	else
	{
		write(1, "Error\nProgramm accepts only 1 argument\n", 39);
		exit(EXIT_FAILURE);
	}
	
	return (0);
}

// mlx_hook - for different events (mouse movements, close the window etc)
// mlx_key_hook - only for keyboard events
//need to handle cntr c to have no leaks???

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:28 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 19:23:27 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
Is not too big to play
Has to be surrounded by walls
No empty lines anywhere in the map
No other characters besides 1, 0, W, E, N, S,
Only one player
Empty map case
Invalid extension (only .cub allowed)
Map does not exist
No arguments or to many arguments
New lines
Check every error case with valgrind
*/

int	read_map(char *map_adress, t_game_info *game)
{
	int		file;

	file = open(map_adress, O_RDONLY);
	if (file == -1)
	{
		close(file);
		handle_error(game, file, "Error\nFile does not exist\n", NULL);
	}
	separate_textures_and_map(game, file, map_adress);
	close(file);
	check_map(game);
	return (1);
}

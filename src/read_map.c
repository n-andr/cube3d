/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:28 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/18 22:53:33 by nandreev         ###   ########.fr       */
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
char	*handle_new_line(t_game_info *game, char *line, int row, int file)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (NULL);
	if (line[0] == '\n' || row == game->rows - 1)
	{
		game->map[row] = malloc(sizeof(char) * ft_strlen(line) + 1);
		if (game->map[row] == NULL)
			handle_error(game, file, "Error\nMemory allocation failed\n");
		ft_strlcpy (game->map[row], line, (ft_strlen(line) + 1));
		return (line);
	}
	while (line[i] && line[i] != '\n')
	{
		i++;
	}
	game->map[row] = malloc(sizeof(char) * (i + 1));
	if (game->map[row] == NULL)
		return (NULL);
	ft_strlcpy (game->map[row], line, (i + 1));
	return (line);
}

void	fill_map(char *map_adress, t_game_info *game)
{
	int		file;
	int		i;
	char	*line;

	file = open(map_adress, O_RDONLY);
	i = 0;
	game->map = malloc(sizeof(char *) * (game->rows + 1));
	if (game->map == NULL)
		handle_error(game, file, "Error\nMemory allocation failed\n");
	line = get_next_line(file);
	handle_new_line(game, line, i, file);
	while (line)
	{
		free(line);
		i ++;
		line = get_next_line (file);
		handle_new_line(game, line, i, file);
	}
	free(line);
	game->map[game->rows] = NULL;
	close(file);
	check_map(game);
	return ;
}

int	read_map(char *map_adress, t_game_info *game)
{
	int		file;
	char	*line;

	game->map = NULL;
	file = open(map_adress, O_RDONLY);
	if (file == -1)
	{
		write(1, "Error\nMap does not exist\n", 25);
		close(file);
		exit(EXIT_FAILURE);
	}
	game->rows = 0;
	line = get_next_line(file);
	// add function to check textures
	// change from here to skip empty lines and textures info before map 

	if (line == NULL)
		handle_error(game, file, "Error\nEmpty map or malloc failed\n");
	while (line)
	{
		free(line);
		game->rows ++;
		line = get_next_line (file);
	}
	free(line);
	close(file);
	fill_map(map_adress, game);

	// debug
	printf("final map:\n");
	for (int i = 0; i < game->rows; i++)
	{
		printf("%s\n", game->map[i]);
	}
	// end debug
	return (1);
}

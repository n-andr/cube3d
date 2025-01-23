/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:28:50 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/23 19:22:48 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	handle_new_line(t_game_info *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] == '\n')
			handle_error(game, -1,
				"Error\nEmpty line in of after the map\n", NULL);
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*skipp_textures(char *line, int file)
{
	while (line && line[0] && ((line[0] == '\n')
			|| (line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A')
			|| (line[0] == 'C' && line[1] == ' ')
			|| (line[0] == 'F' && line[1] == ' ')))
	{
		free(line);
		line = get_next_line(file);
	}
	return (line);
}

void	save_map(t_game_info *game, char *file_adress)
{
	int		i;
	char	*line;
	int		file;

	file = open(file_adress, O_RDONLY);
	game->map = malloc(sizeof(char *) * (game->rows + 1));
	if (game->map == NULL)
		handle_error(game, file, "Error\nMemory allocation failed\n", NULL);
	i = 0;
	line = get_next_line(file);
	line = skipp_textures(line, file);
	while (line)
	{
		game->map[i] = ft_calloc(game->columns + 1, sizeof(char));
		if (game->map[i] == NULL)
			handle_error(game, file, "Error\nMemory allocation failed\n", line);
		ft_strlcpy(game->map[i], line, (ft_strlen(line) + 1));
		ft_memset(game->map[i] + ft_strlen(line), ' ',
			game->columns - ft_strlen(line));
		free(line);
		i++;
		line = get_next_line(file);
	}
	game->map[i] = NULL;
	close(file);
	handle_new_line(game);
}

void	separate_textures_and_map(t_game_info *game,
			int file, char *file_adress)
{
	char	*line;

	line = get_next_line(file);
	line = skipp_textures(line, file);
	while (line)
	{
		game->rows++;
		if (ft_strlen(line) > game->columns)
			game->columns = ft_strlen(line);
		free(line);
		line = get_next_line(file);
	}
	close(file);
	save_map(game, file_adress);
	get_textures(game, file_adress);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:28:50 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/20 00:38:27 by nandreev         ###   ########.fr       */
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
			handle_error(game, -1, "Error\nEmpty line in the map\n");
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = ' '; // change new line to space to remove new line
			j++;
		}
		i++;
	}
}

void	save_map(t_game_info *game, int file, int map_len, int tex_len, char *file_adress)
{
	int		i;
	char	*line;

	game->map = malloc(sizeof(char *) * (map_len + 1));
	if (game->map == NULL)
		handle_error(game, file, "Error\nMemory allocation failed\n");
	i = 0;
	file = open(file_adress, O_RDONLY);
	line = get_next_line(file);
	while (tex_len > 0)
	{
		tex_len--;
		free(line);
		line = get_next_line(file);
	}
	while (line)
	{
		game->map[i] = malloc(sizeof(char) * ft_strlen(line) + 1);
		if (game->map[i] == NULL)
			handle_error(game, file, "Error\nMemory allocation failed\n");
		ft_strlcpy(game->map[i], line, (ft_strlen(line) + 1));
		free(line);
		i++;
		line = get_next_line(file);
	}
	game->map[i] = NULL;
	close(file);
	handle_new_line(game);
	// debug
	printf("save map function:\n");
	for (int i = 0; i < game->rows; i++)
	{
		printf("%s\n", game->map[i]);
	}
	// end debug
}


void		separate_textures_and_map(t_game_info *game, int file, char *file_adress)
{
	char	*line;
	int		map_len;
	int		textures_len;
	
	map_len = 0;
	textures_len = 0;
	line = get_next_line(file);
	while (line && line[0] && ((line[0] == '\n')
		|| (line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'F' && line[1] == ' ')))
	{
		textures_len++;
		free(line);
		line = get_next_line(file);
	}
	while (line)
	{
		map_len++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	save_map(game, file, map_len, textures_len, file_adress);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:32:21 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/19 18:10:19 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	check_texture(t_game_info *game, int file)
{
	if (game->textures.north == NULL)
		handle_error(game, file, "Error\nNo north texture\n");
	if (game->textures.south == NULL)
		handle_error(game, file, "Error\nNo south texture\n");
	if (game->textures.west == NULL)
		handle_error(game, file, "Error\nNo west texture\n");
	if (game->textures.east == NULL)
		handle_error(game, file, "Error\nNo east texture\n");
	if (game->textures.floor == NULL)
		handle_error(game, file, "Error\nNo floor color\n");
	if (game->textures.ceiling == NULL)
		handle_error(game, file, "Error\nNo ceiling color\n");
	return (true);
}

void assign_texture(t_game_info *game, char *line, void *texture, int file)
{
	int i;

	i = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	line = line + i;
	if (texture != NULL)
		handle_error(game, file, "Error\nSame texture listed more than once\n");
	texture = mlx_xpm_file_to_image(game->mlx, line, &game->img_width, &game->img_height); // check if it is correct way to assign texture
}

void	get_textures(t_game_info *game, int file)
{
	char	*line;

	line = get_next_line(file);
	if (line == NULL)
		handle_error(game, file, "Error\nEmpty file\n");
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			assign_texture(game, line + 2, game->textures.north, file);
		else if (line[0] == 'S' && line[1] == 'O')
			assign_texture(game, line + 2, game->textures.south, file);
		else if (line[0] == 'W' && line[1] == 'E')
			assign_texture(game, line + 2, game->textures.west, file);
		else if (line[0] == 'E' && line[1] == 'A')
			assign_texture(game, line + 2, game->textures.east, file);
		else if (line[0] == 'F')
			assign_texture(game, line + 1, game->textures.floor, file); // check if it is correct way to assign RGB colour
		else if (line[0] == 'C')
			assign_texture(game, line + 1, game->textures.ceiling, file); // check if it is correct way to assign RGB colour
		free(line);
		line = get_next_line (file);
	}
	free(line);
	check_texture(game, file);
	close(file);
}

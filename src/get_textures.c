/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:32:21 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/24 19:40:36 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	is_xmp(char *line)
{
	if (line[ft_strlen(line) - 4] == '.' && line[ft_strlen(line) - 3]
		== 'x' && line[ft_strlen(line) - 2]
		== 'p' && line[ft_strlen(line) - 1] == 'm')
		return (true);
	return (false);
}

void	assign_texture(t_game_info *game, char *line, void **img, int file)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
	{
		i++;
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (*img != NULL)
		handle_error(game, file,
			"Error\nSame texture listed more than once\n", line);
	if (is_xmp(line + i) == true)
		*img = mlx_xpm_file_to_image(game->mlx, line + i,
				&game->textures.width, &game->textures.height);
	else
		handle_error(game, file, "Error\nWrong texture format\n", line);
}

void	ft_set_textures_params(t_game_info *game)
{
	game->textures.n_data = mlx_get_data_addr(game->textures.north_img,
			&game->textures.bpp, &game->textures.size_line,
			&game->textures.endian);
	game->textures.s_data = mlx_get_data_addr(game->textures.south_img,
			&game->textures.bpp, &game->textures.size_line,
			&game->textures.endian);
	game->textures.w_data = mlx_get_data_addr(game->textures.west_img,
			&game->textures.bpp, &game->textures.size_line,
			&game->textures.endian);
	game->textures.e_data = mlx_get_data_addr(game->textures.east_img,
			&game->textures.bpp, &game->textures.size_line,
			&game->textures.endian);
	if (!(game->textures.n_data) || !(game->textures.s_data)
		|| !(game->textures.w_data) || !(game->textures.e_data))
	{
		printf("Error: Failed to retrieve data address ");
		printf("for one or more textures\n");
		exit(EXIT_FAILURE);
	}
}

void	extract_line(t_game_info *game, char *line, int file)
{
	if (line[0] == 'N' && line[1] == 'O')
		assign_texture(game, line, (void **)&game->textures.north_img, file);
	else if (line[0] == 'S' && line[1] == 'O')
		assign_texture(game, line, (void **)&game->textures.south_img, file);
	else if (line[0] == 'W' && line[1] == 'E')
		assign_texture(game, line, (void **)&game->textures.west_img, file);
	else if (line[0] == 'E' && line[1] == 'A')
		assign_texture(game, line, (void **)&game->textures.east_img, file);
	else if (line[0] == 'F')
		assign_colour(game, line, &game->textures.floor, file);
	else if (line[0] == 'C')
		assign_colour(game, line, &game->textures.ceiling, file);
}

void	get_textures(t_game_info *game, char *file_adress)
{
	char	*line;
	int		file;

	file = open(file_adress, O_RDONLY);
	if (file == -1)
	{
		write(1, "Error\nFile does not exist\n", 26);
		close(file);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(file);
	if (line == NULL)
		handle_error(game, file, "Error\nEmpty file\n", line);
	while (line)
	{
		extract_line(game, line, file);
		free(line);
		line = get_next_line (file);
	}
	free(line);
	check_texture_and_col(game, file);
	close(file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:32:21 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/24 02:01:50 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	check_texture(t_game_info *game, int file)
{
	if (game->textures.north_img == NULL)
		handle_error(game, file, "Error\nNo north_img texture\n", NULL);
	if (game->textures.south_img == NULL)
		handle_error(game, file, "Error\nNo south_img texture\n", NULL);
	if (game->textures.west_img == NULL)
		handle_error(game, file, "Error\nNo west_img texture\n", NULL);
	if (game->textures.east_img == NULL)
		handle_error(game, file, "Error\nNo east_img texture\n", NULL);
	if (game->textures.floor == -1)
		handle_error(game, file, "Error\nNo floor colour\n", NULL);
	if (game->textures.ceiling == -1)
		handle_error(game, file, "Error\nNo ceiling colour\n", NULL);
	return (true);
}

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

//The resulting integer's binary representation is 0xTTRRGGBB,
//where TT is the transparency, RR is the red channel,
//GG is the green channel, and BB is the blue channel.
//TTTTTTTT RRRRRRRR GGGGGGGG BBBBBBBB

int	rgb_to_int(int r, int g, int b)
{
	int	t;

	t = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}

bool	digits_only_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit((int)str[i]) != 0)
			i ++;
		else
			return (false);
	}
	return (true);
}

int	colour_to_int(char *line, int i, t_game_info *game, int file)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	r = 0;
	g = 0;
	b = 0;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	rgb = ft_split(line + i, ',');
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL
		|| digits_only_str(rgb[0]) == false || digits_only_str(rgb[1]) == false
		|| digits_only_str(rgb[2]) == false)
	{
		free_array(rgb);
		handle_error(game, file, "Error\nWrong colour format\n", line);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		handle_error(game, file, "Error\nWrong colour format\n", line);
	return (rgb_to_int(r, g, b));
}

void assign_colour(t_game_info *game, char *line, int *colour, int file)
{
	int	i;
	int	rgb;

	i = 1;
	while (line[i] == ' ')
	{
		i++;
	}
	if (*colour != -1)
	{
		handle_error(game, file,
			"Error\nSame colour listed more than once\n", line);
	}
	rgb = colour_to_int(line, i, game, file);
	*colour = rgb;
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
		if (line[0] == 'N' && line[1] == 'O')
			assign_texture(game, line,
				(void **)&game->textures.north_img, file);
		else if (line[0] == 'S' && line[1] == 'O')
			assign_texture(game, line,
				(void **)&game->textures.south_img, file);
		else if (line[0] == 'W' && line[1] == 'E')
			assign_texture(game, line,
				(void **)&game->textures.west_img, file);
		else if (line[0] == 'E' && line[1] == 'A')
			assign_texture(game, line,
				(void **)&game->textures.east_img, file);
		else if (line[0] == 'F')
			assign_colour(game, line, &game->textures.floor, file);
		else if (line[0] == 'C')
			assign_colour(game, line, &game->textures.ceiling, file);
		free(line);
		line = get_next_line (file);
	}
	free(line);
	check_texture(game, file);
	close(file);
}

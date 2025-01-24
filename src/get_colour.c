/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:36:06 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/24 19:36:07 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	assign_colour(t_game_info *game, char *line, int *colour, int file)
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

bool	check_texture_and_col(t_game_info *game, int file)
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

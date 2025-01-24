/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:27:23 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/24 14:31:59 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_wall_side_ident(t_ray ray, t_line *line)
{
	if (ray.ray_y_dir == 1)
	{
		if (line->hit_hor_wall)
			line->s_wall_side = 1;
		else if (ray.ray_x_dir == 1)
			line->e_wall_side = 1;
		else
			line->w_wall_side = 1;
	}
	else if (ray.ray_y_dir == -1)
	{
		if (line->hit_hor_wall)
			line->n_wall_side = 1;
		else if (ray.ray_x_dir == 1)
			line->e_wall_side = 1;
		else
			line->w_wall_side = 1;
	}
}

void	ft_hor_vert_steps(t_ray *hor, t_ray *vert, t_game_info *game)
{
	int	intersection;

	while (1)
	{
		hor->len += ft_hor_step(hor);
		intersection = ft_check_intersection(game, hor);
		if (intersection)
			break ;
	}
	if (intersection == -1 || hor->len < 0)
		hor->len = INT_MAX;
	while (1)
	{
		vert->len += ft_vert_step(vert);
		intersection = ft_check_intersection(game, vert);
		if (intersection)
			break ;
	}
	if (intersection == -1 || vert->len < 0)
		vert->len = INT_MAX;
	if (hor->correct_len < 0)
		hor->correct_len = INT_MAX;
	if (vert->correct_len < 0)
		vert->correct_len = INT_MAX;
}

int	ft_choose_len(t_ray hor, t_ray vert, t_line *lines, int i)
{
	if (vert.correct_len < hor.correct_len)
	{
		lines[i].offset_x = (int)vert.ray_y % CELL_SIZE;
		ft_wall_side_ident(vert, &lines[i]);
		return (vert.correct_len);
	}
	else if (vert.correct_len > hor.correct_len)
	{
		lines[i].offset_x = (int)hor.ray_x % CELL_SIZE;
		lines[i].hit_hor_wall = 1;
		ft_wall_side_ident(vert, &lines[i]);
		return (hor.correct_len);
	}
	else
	{
		ft_hor_vert_intersec_def(lines, i);
		ft_wall_side_ident(vert, &lines[i]);
		return (vert.correct_len);
	}
}

void	ft_raycasting(t_game_info *game)
{
	int		i;
	t_line	*lines;

	game->first_ray_angle = game->player.p_angle - M_PI / 6;
	lines = (t_line *)calloc(S_W + 1, sizeof(t_line));
	if (lines == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < S_W)
	{
		ft_line_def(&lines[i]);
		lines[i].y_top = 0;
		lines[i].correct_len = ft_find_intersections(game, i, lines);
		lines[i].high = S_H * CELL_SIZE / lines[i].correct_len;
		lines[i].x = i;
		lines[i].y1 = (S_H - lines[i].high) / 2;
		lines[i].y2 = S_H - lines[i].y1;
		i++;
	}
	game->lines = lines;
}

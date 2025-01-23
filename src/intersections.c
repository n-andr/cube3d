/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:01:08 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/23 19:01:53 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	ft_hor_step(t_ray *hor)
{
	float	y_next_bord;
	int		hor_len;

	hor->row = hor->row + hor->ray_y_dir;
	if (hor->ray_y_dir == 1)
		y_next_bord = hor->row * CELL_SIZE;
	else
		y_next_bord = (hor->row + 1) * CELL_SIZE;
	hor->y_step = fabs(y_next_bord - hor->ray_y);
	hor->x_step = hor->y_step / fabs(tan(hor->angle));
	hor->ray_y = y_next_bord;
	if (hor->angle)
		hor->ray_x = hor->ray_x + hor->ray_x_dir * hor->x_step;
	hor->col = (hor->ray_x + 0.01 * hor->ray_x_dir) / CELL_SIZE;
	hor_len = round(sqrt(hor->x_step * hor->x_step + hor->y_step
				* hor->y_step));
	return (hor_len);
}

int	ft_vert_step(t_ray *vert)
{
	int		vert_len;
	float	x_next_bord;

	vert->col = vert->col + vert->ray_x_dir;
	if (vert->ray_x_dir == 1)
		x_next_bord = vert->col * CELL_SIZE;
	else
		x_next_bord = (vert->col + 1) * CELL_SIZE;
	vert->x_step = fabsf(x_next_bord - vert->ray_x);
	vert->y_step = vert->x_step * fabs(tan(vert->angle));
	vert->ray_x = x_next_bord;
	if (vert->angle)
		vert->ray_y = vert->ray_y + vert->ray_y_dir * vert->y_step;
	vert->row = ((vert->ray_y + 0.01 * vert->ray_y_dir) / CELL_SIZE);
	vert_len = round(sqrt(vert->x_step * vert->x_step + vert->y_step
				* vert->y_step));
	return (vert_len);
}

int	ft_check_intersection(t_game_info *game, t_ray *ray)
{
	if ((ray->col >= game->columns || ray->row >= game->rows) || (ray->col < 0
			|| ray->row < 0))
		return (-1);
	if (game->map[ray->row][ray->col] == '1')
		return (1);
	return (0);
}

int	ft_find_intersections(t_game_info *game, int i, t_line *lines)
{
	t_ray	hor;
	t_ray	vert;
	float	delta_angle;


	delta_angle = (game->player.fov_angle * i) / S_W;
	ft_rays_def(&hor, &vert, game, delta_angle);
	ft_ray_dir_def(&hor, &vert);
	ft_hor_vert_steps(&hor, &vert, game);
	lines[i].hit_hor_wall = 0;
	hor.correct_len = ft_len_def(game, &hor);
	vert.correct_len = ft_len_def(game, &vert);
	if (hor.correct_len < 0)
		hor.correct_len = INT_MAX;
	if (vert.correct_len < 0)
		vert.correct_len = INT_MAX;
	return (ft_choose_len(hor, vert, lines, i));
}

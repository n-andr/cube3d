/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_defs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:27:12 by mkokorev          #+#    #+#             */
/*   Updated: 2025/01/24 14:38:44 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_ray_dir_def(t_ray *hor, t_ray *vert)
{
	if ((hor->angle > 0 && hor->angle < M_PI) || hor->angle > 2 * M_PI)
	{
		hor->ray_y_dir = 1;
		vert->ray_y_dir = 1;
	}
	else
	{
		hor->ray_y_dir = -1;
		vert->ray_y_dir = -1;
	}
	if (hor->angle > M_PI / 2 && hor->angle < 3 * M_PI / 2)
	{
		hor->ray_x_dir = -1;
		vert->ray_x_dir = -1;
	}
	else
	{
		hor->ray_x_dir = 1;
		vert->ray_x_dir = 1;
	}
}

int	ft_len_def(t_game_info *game, t_ray *ray)
{
	int		correct_len;
	float	len;
	float	del_x;
	float	del_y;
	float	angle;

	del_x = fabs(ray->ray_x - game->player.x);
	del_y = fabs(ray->ray_y - game->player.y);
	angle = game->player.p_angle - ray->angle;
	len = sqrt(del_x * del_x + del_y * del_y);
	correct_len = round(fabs(len * cos(angle)));
	return (correct_len);
}

void	ft_rays_def(t_ray *hor, t_ray *vert,
			t_game_info *game, float delta_angle)
{
	hor->angle = game->first_ray_angle + delta_angle;
	hor->len = 0;
	hor->correct_len = 0;
	hor->ray_x = game->player.x;
	hor->ray_y = game->player.y;
	hor->col = game->player.p_position_col;
	hor->row = game->player.p_position_row;
	hor->ray_x_dir = 0;
	hor->ray_y_dir = 0;
	hor->x_step = 0;
	hor->y_step = 0;
	vert->angle = hor->angle;
	vert->len = hor->len;
	vert->ray_x = hor->ray_x;
	vert->ray_y = hor->ray_y;
	vert->col = hor->col;
	vert->row = hor->row;
	vert->correct_len = hor->correct_len;
	vert->ray_x_dir = hor->ray_x_dir;
	vert->ray_y_dir = hor->ray_y_dir;
	vert->x_step = hor->x_step;
	vert->y_step = hor->y_step;
}

void	ft_line_def(t_line *line)
{
	line->e_wall_side = 0;
	line->s_wall_side = 0;
	line->w_wall_side = 0;
	line->n_wall_side = 0;
	line->high = 0;
	line->correct_len = 0;
	line->hit_hor_wall = 0;
}

void	ft_hor_vert_intersec_def(t_line *lines, int i)
{
	if (i && lines)
		lines[i].hit_hor_wall = lines[i - 1].hit_hor_wall;
}



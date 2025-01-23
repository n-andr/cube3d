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

void	ft_hor_vert_intersec_def(t_line *lines, int i)
{
	if (i && lines)
		lines[i].hit_hor_wall = lines[i - 1].hit_hor_wall;
}

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

void	ft_rays_def(t_ray *hor, t_ray *vert,
			t_game_info *game, float delta_angle)
{
	hor->angle = game->first_ray_angle + delta_angle;
	vert->angle = hor->angle;
	vert->len = 0;
	hor->len = 0;
	hor->ray_x = game->player.x;
	hor->ray_y = game->player.y;
	vert->ray_x = game->player.x;
	vert->ray_y = game->player.y;
	vert->col = game->player.p_position_col;
	vert->row = game->player.p_position_row;
	hor->col = game->player.p_position_col;
	hor->row = game->player.p_position_row;
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

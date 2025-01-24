/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/24 19:28:19 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define CELL_SIZE 128
# define MINI_CELL_SIZE 16
# define STEP_SIZE 8
# define TURN_ANGLE 0.065
# define PLAYER_SIZE 8
# define MINI_PLAYER_SIZE 16
# define S_W 1920
# define S_H 1020
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./mlx/mlx.h"
# include "mlx/mlx.h"
# include "src/get_next_line/get_next_line.h"
# include "src/libft/libft.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdbool.h>

// if complains about include "mlx.h"
//sudo cp libmlx.a /usr/local/lib/
// sudo cp mlx.h /usr/local/include/

typedef struct s_textures
{
	void	*north_img;
	void	*south_img;
	void	*west_img;
	void	*east_img;
	void	*gun_img;
	int		floor;
	int		ceiling;
	char	*n_data;
	char	*s_data;
	char	*w_data;
	char	*e_data;
	void	*gun_data;
	int		x_gun;
	int		y_gun;
	int		width;
	int		height;
	int		gun_width;
	int		gun_height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_textures;

typedef struct s_player
{
	int			x;
	int			y;
	int			p_position_row;
	int			p_position_col;
	float		p_angle;
	float		fov_angle;
}	t_player;

typedef struct s_ray
{
	float		x_step;
	float		y_step;
	int			ray_x_dir;
	int			ray_y_dir;
	float		ray_x;
	float		ray_y;
	int			row;
	int			col;
	int			len;
	int			correct_len;
	float		angle;
}	t_ray;

typedef struct s_line
{
	int				x;
	int				y1;
	int				y2;
	int				offset_x;
	int				y_top;
	int				high;
	int				correct_len;
	int				hit_hor_wall;
	int				s_wall_side;
	int				n_wall_side;
	int				w_wall_side;
	int				e_wall_side;
}	t_line;

typedef struct s_draw_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_draw_data;

typedef struct s_key_state
{
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		mouse_turn;
}	t_key_state;

typedef struct s_game_info
{
	char		**map;
	int			rows;
	int			columns;
	int			map_width;
	int			map_height;
	float		delt_angle;
	float		first_ray_angle;
	void		*mlx;
	void		*window;
	int			step;
	t_key_state	key_state;
	t_draw_data	drawing_data;
	t_textures	textures;
	t_player	player;
	t_line		*lines;
}	t_game_info;

typedef struct s_vars
{
	t_game_info		*game;
}				t_vars;

//parsing
int				read_map(char *map, t_game_info *game);
void			check_map(t_game_info *game);
void			separate_textures_and_map(t_game_info *game,
					int file, char *file_adress);
void			get_textures(t_game_info *game, char *file_adress);
void			assign_colour(t_game_info *game, char *line, int *colour, int file);
bool			check_texture_and_col(t_game_info *game, int file);



//int		has_valid_path(t_game_info *game);
//void	find_p(t_game_info *game, char **map);
//int		key_pressed(int key, t_game_info *game);

//elements check
void			characters_check(t_game_info *game);
void			player_position_check(t_game_info *game);
int				p_check(t_game_info *game);
bool			map_is_one_piece(t_game_info *game);
bool			is_closed(t_game_info *game);

//math
void			ft_raycasting(t_game_info	*game);
void			ft_line_def(t_line *line);
void			ft_ray_dir_def(t_ray *hor, t_ray *vert);
int				ft_len_def(t_game_info *game, t_ray *ray);
void			ft_rays_def(t_ray *hor, t_ray *vert,
					t_game_info *game, float delta_angle);
void			ft_line_def(t_line *line);
void			ft_hor_vert_intersec_def(t_line *lines, int i);
int				ft_find_intersections(t_game_info *game, int i, t_line *lines);
int				ft_check_intersection(t_game_info *game, t_ray *ray);
void			ft_hor_vert_steps(t_ray *hor, t_ray *vert, t_game_info *game);
int				ft_hor_step(t_ray *hor);
int				ft_vert_step(t_ray *vert);
int				ft_choose_len(t_ray hor, t_ray vert, t_line *lines, int i);


// graphics
void			ft_game_draw(t_game_info	*game);
int				handle_input(int keysym, t_vars *data);
int				x_close(t_vars *data);
void			ft_set_textures_params(t_game_info *game);
// void	open_img(t_game_info *game);
// void	load_map_graphics(t_game_info *game);
void			draw_cell(int x, int y, int color, t_game_info *game);
void			ft_draw_vertikal(t_game_info *game,
					t_line lines, unsigned int color);
void			ft_floor_ceiling_colour(t_game_info *game);
unsigned int	ft_get_pixel_color(t_game_info *game,
					t_line line, int x, int y);
void			render_minimap(t_game_info *game);
void			draw_player(t_game_info *game, int color);
void			ft_ceiling_color_change(t_game_info *game);


// //moves
void			move_p(t_game_info *game, int key);
void			turn_p(t_game_info *game, int key);
void			turn_right(t_game_info *game);
void			turn_left(t_game_info *game);
int				mouse_move(int x, int y, t_game_info *game);
int				key_press(int key, t_game_info *game);
int				key_release(int key, t_game_info *game);
int				render_and_update(t_game_info *game);



//free
void			handle_error(t_game_info *game, int file,
					char *message, char *str);
// void	free_map(t_game_info *game);
// void	free_check_map(char **map);
void			free_array(char **array);
void			free_textures(t_game_info *game);
int				close_game(t_game_info *game, int exit_status);

#endif

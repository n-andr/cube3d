/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2025/01/10 19:54:20 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
// # define IMG_WIDTH 32
// # define IMG_HEIGHT 32
# define CELL_SIZE 64
# define MINI_CELL_SIZE 16
# define STEP_SIZE 16
# define TURN_ANGLE (M_PI / 24)
//# define TURN_ANGLE (M_PI / 4)
// TURN_ANGLE = 15 degrees
# define PLAYER_SIZE (MINI_CELL_SIZE / 2)
# define S_W 1280
# define S_H 720

# include <fcntl.h>
# include <math.h>
#include <limits.h>
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
	//void	*player;
	//void	*collectible;
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	int		floor;
	int		ceiling;
}	t_textures;

typedef struct	s_player
{
	int			x;
	int			y;
	int			p_position_row;
	int			p_position_col;
	float		p_angle;
	float		fov_angle;
}	t_player;

typedef struct	s_ray
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

typedef struct	s_line
{
	int	x;
	int y1;
	int y2;
	int color;
	int	high;
	int	correct_len;
	int	hit_hor_wall;
}	t_line;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_game_info
{
	char		**map;
	int			rows;
	int			columns;
	int			img_width;
	int			img_height;
	int			colour;
	float		delt_angle;
	float		first_ray_angle;
	float		epsilon;
	void		*mlx;
	void		*window;
	t_data		drawing_data;
	t_textures	textures;
	t_player	player;
	t_line		*lines;
}	t_game_info;

typedef struct s_vars
{
	void			*mlx;
	void			*img;
	void			*win;
	t_game_info		*game;
}				t_vars;

int		read_map(char *map, t_game_info *game);
void	check_map(t_game_info *game);
void	separate_textures_and_map(t_game_info *game, int file, char *file_adress);
void	get_textures(t_game_info *game, char *file_adress);

//int		has_valid_path(t_game_info *game);
//void	find_p(t_game_info *game, char **map);
//int		key_pressed(int key, t_game_info *game);

//elements check
void	characters_check(t_game_info *game);
void	player_position_check(t_game_info *game);
int		p_check(t_game_info *game);
bool	map_is_one_piece(t_game_info *game);
bool	is_closed(t_game_info *game);

//math
void    ft_raycasting(t_game_info	*game);

// graphics
void	ft_game_draw(t_game_info	*game);
int		handle_input(int keysym, t_vars *data);
int		x_close(t_vars *data);
// void	open_img(t_game_info *game);
// void	load_map_graphics(t_game_info *game);
void	render_map(t_game_info *game);
void	draw_cell(int x, int y, int color, t_game_info *game);
void	ft_draw_vertikal(t_game_info *game, t_line lines);


// //moves
void	move_p(t_game_info *game, int key);
void	turn_p(t_game_info *game, int key);


//free
void	handle_error(t_game_info *game, int file, char *message, char *str);
// void	free_map(t_game_info *game);
// void	free_check_map(char **map);
void	free_array(char **array);
void	free_textures(t_game_info *game);
int	close_game(t_game_info *game, int exit_status);


#endif

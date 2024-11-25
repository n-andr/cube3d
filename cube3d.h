/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:21:53 by nandreev          #+#    #+#             */
/*   Updated: 2024/11/22 19:34:27 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
// # define IMG_WIDTH 32
// # define IMG_HEIGHT 32
# define CELL_SIZE 64
# define S_W 1280
# define S_H 720
# define M_PI 3.14159265358979323846

# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "src/get_next_line/get_next_line.h"
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
	void	*floor;
	void	*ceiling;
}	t_textures;

typedef struct	v_player_coord
{
	int			x;
	int			y;
}	t_player_coord;


typedef struct	s_wall_coord
{
	int			x;
	int			y;
}	t_wall_coord;

typedef struct s_game_info
{
	char		**map;
	int			rows;
	int			columns;
	int			p_position_row;
	int			p_position_col;
	float		ray_x;
	float		ray_y;
	int			img_width;
	int			img_height;
	int			colour;
	float		delt_angle;
	float		p_angle;
	float		first_ray_angle;
	//int			collectibles;
	//int			moves_count;
	//int			c_count;
	//int			exit_check;
	void		*mlx;
	void		*window;
	t_textures	textures;
    t_player_coord	player;
    t_wall_coord	wall;
}	t_game_info;

typedef struct s_daa
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

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

//math
void    ft_raycasting(t_game_info	*game);

// graphics
void	ft_game_draw(t_game_info	*game);
int		handle_input(int keysym, t_vars *data);
int		x_close(t_vars *data);
// void	open_img(t_game_info *game);
// void	load_map_graphics(t_game_info *game);

// //moves
// void	move_p(t_game_info *game, int keycode);
// void	count_moves(t_game_info *game);

//free
void	handle_error(t_game_info *game, int file, char *message);
void	free_map(t_game_info *game);
void	free_check_map(char **map);
//int		close_game(t_game_info *game);

//libft
char	*ft_itoa(int n);

#endif

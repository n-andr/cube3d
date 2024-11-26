#include "../cube3d.h"

void	ft_dot_draw(t_data *data, t_game_info	*game)
{
    char	*dst;

    dst = data->addr + (game->player.x * data->line_length
            + game->player.y * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = game->colour;
}

//void	line_draw(t_data *img, int mat1, int mat2, t_game_info *game)
//{
//	int				k;
//	int				i;
//	t_coordinate	xy;
//	int				y_comp;
//
//	if (mat1.x > mat2.x)
//		return (matrix_line_draw(&(*img), mat2, mat1, colour));
//	if (mat1.x == mat2.x)
//		return (draw_vertikal(&(*img), mat1, mat2.y, colour));
//	i = 1;
//	xy.y = mat1.y;
//	xy.x = mat1.x;
//	k = (100 * (mat2.y - mat1.y) / (mat2.x - mat1.x));
//	while (abs(xy.x - mat2.x) > 0)
//	{
//		y_comp = 2 * xy.y + 1;
//		if (y_comp - xy.y > 0)
//			draw_vertikal(&(*img), xy, (100 * mat1.y + k * i) / 100, colour);
//		xy.y = (100 * mat1.y + k * i++) / 100;
//		xy.x++;
//	}
//	my_mlx_pixel_put(&(*img), xy, colour);
//	return ;
//}
//
//void	draw_vertikal(t_data *img, t_coordinate xy, int y2, int colour)
//{
//	while (abs(xy.y - y2) > 0)
//	{
//		my_mlx_pixel_put(&(*img), xy, colour);
//		if (xy.y < y2)
//			xy.y++;
//		else
//			xy.y--;
//	}
//	my_mlx_pixel_put(&(*img), xy, colour);
//	return ;
//}

void	ft_game_draw(t_game_info	*game)
{
    void			*mlx_win;
    t_data			img;
    t_vars			data;

    data.game = game;
    mlx_win = mlx_new_window(game->mlx, S_W,
            S_H, "Cube3D");
    img.img = mlx_new_image(game->mlx, S_W, S_H);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
            &img.line_length, &img.endian);
    ft_dot_draw(&img, game);
    //ft_line_draw(&img, game);
    mlx_put_image_to_window(game->mlx, mlx_win, img.img, 0, 0);
    data.mlx = game->mlx;
    data.win = mlx_win;
    data.img = img.img;
    mlx_key_hook(mlx_win, handle_input, &data);
    mlx_hook(mlx_win, 17, 1L << 17, x_close, &data);
    mlx_loop(game->mlx);
}
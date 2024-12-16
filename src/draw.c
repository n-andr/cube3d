#include "../cube3d.h"

void	ft_dot_draw(t_data *data, t_line lines)
{
    char	*dst;

    	printf("x: %d, y1: %d\n", lines.x, lines.y1);
    dst = data->addr + (lines.y1 * data->line_length
            + lines.x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = lines.color;
}

void	ft_draw_vertikal(t_data *img, t_line lines)
{

	while (abs(lines.y1 - lines.y2) > 0)
	{
        if (lines.high < S_H)
			ft_dot_draw(&(*img), lines);
		lines.y1 = lines.y1 + 1;
	}
	ft_dot_draw(&(*img), lines);
	return ;
}

void	ft_game_draw(t_game_info	*game, t_line *lines)
{
    void			*mlx_win;
    t_data			img;
    t_vars			data;
    int				i;

    data.game = game;
    mlx_win = mlx_new_window(game->mlx, S_W,
            S_H, "Cube3D");
    img.img = mlx_new_image(game->mlx, S_W, S_H);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
            &img.line_length, &img.endian);
    //ft_dot_draw(&img, game);
    i = 0;
    while (i < S_W)
      {
    	ft_draw_vertikal(&img, lines[i]);
        i++;
      }
    mlx_put_image_to_window(game->mlx, mlx_win, img.img, 0, 0);
    data.mlx = game->mlx;
    data.win = mlx_win;
    data.img = img.img;
    mlx_key_hook(mlx_win, handle_input, &data);
    mlx_hook(mlx_win, 17, 1L << 17, x_close, &data);
    mlx_loop(game->mlx);
}

#include "../cube3d.h"

void	ft_dot_draw(t_data *data, t_game_info	*game)
{
    char	*dst;

    dst = data->addr + (game->p_cell_x * data->line_length
            + game->p_cell_y * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = game->colour;
}

void	ft_game_draw(t_game_info	*game)
{
    void			*mlx;
    void			*mlx_win;
    t_data			img;
    t_vars			data;

    data.game = game;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, S_W,
            S_H, "FdF");
    img.img = mlx_new_image(mlx, S_W, S_H);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
            &img.line_length, &img.endian);
    ft_dot_draw(&img, game);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    data.mlx = mlx;
    data.win = mlx_win;
    data.img = img.img;
    mlx_key_hook(mlx_win, handle_input, &data);
    mlx_hook(mlx_win, 17, 1L << 17, x_close, &data);
    mlx_loop(mlx);
}
#include "../cube3d.h"

int	handle_input(int keysym, t_vars *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_image(data->mlx, data->img);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data -> mlx);
        free(data->mlx);
        free_map(data->game);
        exit(0);
    }
    return (1);
}

int	x_close(t_vars *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data -> mlx);
    free(data->mlx);
    free_map(data->game);
    exit(0);
}
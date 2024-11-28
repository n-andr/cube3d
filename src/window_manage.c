#include "../cube3d.h"

int	handle_input(int keysym, t_vars *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_image(data->mlx, data->img);
		//Nata's changes: add free_textures function to avoid memory leaks
		free_textures(data->game);
		//end Natat's changes
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data -> mlx);
        free(data->mlx);
		//Nata's changes: replaced free_map with free_array
		free_array(data->game->map);
        //free_map(data->game);
		//end Nata's changes
        exit(0);
    }
    return (1);
}

int	x_close(t_vars *data)
{
    mlx_destroy_image(data->mlx, data->img);
	//Nata's changes: add free_textures function to avoid memory leaks
	free_textures(data->game);
	//end Nata's changes
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data -> mlx);
    free(data->mlx);
	//Nata's changes: replaced free_map with free_array
	free_array(data->game->map);
    //free_map(data->game);
	//end Nata's changes
    exit(0);
}
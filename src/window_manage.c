#include "../cube3d.h"

int	handle_input(int keysym, t_vars *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_image(data->game->mlx, data->game->drawing_data.img);
		//Nata's changes: add free_textures function to avoid memory leaks
		free_textures(data->game);
		//end Natat's changes
        mlx_destroy_window(data->game->mlx, data->game->window);
        mlx_destroy_display(data -> game->mlx);
        free(data->game->mlx);
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
	if (data->game->drawing_data.img)
		mlx_destroy_image(data->game->mlx, data->game->drawing_data.img);
	//Nata's changes: add free_textures function to avoid memory leaks
	free_textures(data->game);
	//end Nata's changes
	if (data->game->window)
		mlx_destroy_window(data->game->mlx, data->game->window);
	if (data->game->mlx)
	{
		mlx_destroy_display(data->game->mlx);
		free(data->game->mlx);
	}
	//Nata's changes: replaced free_map with free_array
	free_array(data->game->map);
    //free_map(data->game);
	//end Nata's changes
    exit(0);
}
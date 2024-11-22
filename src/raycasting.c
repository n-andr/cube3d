#include "../cube3d.h"
#include <math.h>

void  ft_first_step(t_game_info *game)
{
   float   x_step;
   float   y_first_bord;
   float   y_first_step;

   y_first_bord = game->p_position_row * CELL_SIZE;
   y_first_step = y_first_bord - game->p_cell_y;
   //TODO: change first_ray_angle to the actual ray angle
   x_step = y_first_step / tan(game->first_ray_angle);
   game->ray_x = game->ray_x + x_step;
   game->ray_y = game->ray_y + y_first_step;
   printf("y_first_bord %f\n", y_first_bord);
   printf("first_ray_angle %f\n", game->first_ray_angle);
   printf("y_first_step %f\n", y_first_step);
   printf("x_first_step %f\n", x_step);
   printf("ray_x %f\n", game->ray_x);
   printf("ray_y %f\n", game->ray_y);
}

int  ft_check_intersection(t_game_info   *game)
{
   //check horisontal intersection:
   int i;
   int j;

   j = game->ray_x  / CELL_SIZE;
   i = (game->ray_y - 2) / CELL_SIZE;
   printf("game->map[%d][%d]: %d\n", i, j, game->map[i][j]);
   if (game->map[i][j] == '1')
      return (1);
   else
      return (0);
}

void ft_ray_dir_def(t_game_info *game, int  *ray_x_dir, int  *ray_y_dir)
{
   if (game->first_ray_angle > 0 && game->first_ray_angle < M_PI)
      *ray_y_dir = 1;
   else
      *ray_y_dir = -1;
   if (game->first_ray_angle > M_PI / 2 && game->first_ray_angle < 3 * M_PI / 2)
      *ray_x_dir = -1;
   else
      *ray_x_dir = 1;
}

void  ft_find_intersections(t_game_info  *game)
{
   int   hit_wall;
   int  ray_x_dir;
   int  ray_y_dir;

   hit_wall = 0;
   ft_ray_dir_def(game, &ray_x_dir, &ray_y_dir);
   printf("ray x dir: %d, ray y dir: %d\n", ray_x_dir, ray_y_dir);
   ft_first_step(game);
      if (ft_check_intersection(game))
         hit_wall = 1;
 printf("hit wall: %d\n", hit_wall);
}


   void  ft_raycasting(t_game_info	*game)
   {
   printf("pi: %f\n", M_PI);
   printf("angle: %f\n",game->p_angle);
   printf("p_cell_x: %d\n",game->p_cell_x);
   printf("p_cell_y: %d\n",game->p_cell_y);
   ft_find_intersections(game);
   }

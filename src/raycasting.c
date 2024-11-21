#include "../cube3d.h"
#include <math.h>

void  ft_check_intersection(t_game_info   *game, int *hit_wall)
{
   //find hor intersection
    //find th first hor interection
   int   x_step;
   //int   y_step;
   int   y_first_step;
   int   y_first_bord;

   *hit_wall = 0;
   y_first_bord = game->p_position_row * CELL_SIZE;
   y_first_step = -1 *(game->p_cell_y - y_first_bord);
   x_step = y_first_step / tan(game->first_ray_angle - M_PI);
   printf("y_first_tep %d\n", y_first_step);
   printf("x_first_tep %d\n", x_step);

}

void  ft_find_intersections(t_game_info  *game)
{
   int   hit_wall;

   hit_wall = 0;
  // while (!hit_wall)
  // {
      ft_check_intersection(game, &hit_wall);
      //ft_make_step(game);
 //  }
}


   void  ft_raycasting(t_game_info	*game)
   {
   printf("pi: %f\n", M_PI);
   printf("angle: %f\n",game->p_angle);
   printf("p_x: %d\n",game->p_cell_x);
   printf("p_y: %d\n",game->p_cell_y);
   ft_find_intersections(game);
   }

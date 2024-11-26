#include "../cube3d.h"

void  ft_first_step(t_game_info *game, int ray_x_dir, int ray_y_dir)
{
   float   x_step;
   float   y_first_bord;
   float   y_first_step;


   //look for horisontal intersection:
   y_first_bord = game->p_position_row * CELL_SIZE;
   if (ray_y_dir == 1)
     y_first_bord += CELL_SIZE;
   y_first_step = fabs(y_first_bord - game->player.y);
   //TODO: change first_ray_angle to the actual ray angle
   x_step = fabs(y_first_step / tan(game->first_ray_angle));
   game->ray_x = game->ray_x + ray_x_dir * x_step;
   game->ray_y = game->ray_y + ray_y_dir * y_first_step;
   printf("p_position_raw: %d\n", game->p_position_row);
   printf("y_first_bord %f\n", y_first_bord);
   printf("first_ray_angle %f\n", game->first_ray_angle);
   printf("y_first_step %f\n", y_first_step);
   printf("x_first_step %f\n", x_step);
   printf("ray_x %f\n", game->ray_x);
   printf("ray_y %f\n", game->ray_y);
   //look for vertical intersection:
   ray_x_dir = ray_x_dir;
}

int  ft_check_intersection(t_game_info   *game, int ray_x_dir, int ray_y_dir)
{
   //check horisontal intersection:
   int col;
   int row;

   col = game->ray_x  / CELL_SIZE;
   row = (game->ray_y + ray_y_dir) / CELL_SIZE;
   printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
      return (1);
   else
      return (0);
   //check vertical intersection:
   ray_x_dir = ray_x_dir;
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
   printf("ray_x_dir %d\n", *ray_x_dir);
   printf("ray_y_dir %d\n", *ray_y_dir);
}

int   ft_len_def(t_game_info *game)
{
  float correct_len;
  float len;
  float del_x;
  float del_y;
  float angle;
  //int correct_len;

   del_x = fabs(game->ray_x - game->player.x);
   del_y = fabs(game->ray_y - game->player.y);
   angle = game->p_angle - game->first_ray_angle;
   len = sqrt(del_x * del_x + del_y * del_y);
  //TODO: change the first ray angle to current angle
   correct_len = fabs(len * cos(angle));
   printf("del_x: %f, del_y: %f, angle: %f\n", del_x, del_y, angle);
   printf("len: %f\n", len);
   return (correct_len);
}

int   ft_find_intersections(t_game_info  *game)
{
   int   hit_wall;
   int   ray_x_dir;
   int   ray_y_dir;
   int   steps;
   int   correct_len;

   //work with horizontal intersections
   hit_wall = 0;
   ft_ray_dir_def(game, &ray_x_dir, &ray_y_dir);
   printf("ray x dir: %d, ray y dir: %d\n", ray_x_dir, ray_y_dir);
   printf("hit wall: %d\n", hit_wall);
   steps = 0;
   while (!hit_wall)
     {
        ft_first_step(game, ray_x_dir, ray_y_dir);
        steps++;
        if (ft_check_intersection(game, ray_x_dir, ray_y_dir))
           hit_wall = 1;
     }
   correct_len = ft_len_def(game);
   printf("hit wall: %d\n", hit_wall);
   printf("steps: %d\n", steps);
   printf("correct_len: %d\n", correct_len);
   return (correct_len);
}


   void  ft_raycasting(t_game_info	*game)
{
   printf("pi: %f\n", M_PI);
   printf("angle: %f\n",game->p_angle);
   printf("p_cell_x: %d\n",game->player.x);
   printf("p_cell_y: %d\n",game->player.y);
   ft_find_intersections(game);
}

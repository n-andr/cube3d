#include "../cube3d.h"

void  ft_first_hor_step(t_game_info *game, int ray_x_dir, int ray_y_dir)
{
   float   x_step;
   int   y_next_bord;
   float   y_step;
   int   y_col;


   //look for horisontal intersection:
   y_col = game->ray_y / CELL_SIZE;
   if (ray_x_dir == 1)
     y_col += 1;
   else
      y_col += 1;
   y_next_bord = y_col * CELL_SIZE;
   y_step = fabsf(y_next_bord - game->ray_y);
   //TODO: change first_ray_angle to the actual ray angle
   x_step = fabs(y_step / tan(game->first_ray_angle));
   game->ray_y = game->ray_y + ray_y_dir * y_step;
   game->ray_x = game->ray_x + ray_x_dir * x_step;
   printf("y_next_bord %d\n", y_next_bord);
   //printf("p_position_raw: %d\n", game->p_position_row);
   printf("first_ray_angle %f\n", game->first_ray_angle);
   printf("x_step %f\n", x_step);
   printf("y_step %f\n", y_step);
}

void  ft_first_vert_step(t_game_info *game, int ray_x_dir, int ray_y_dir)
{
   float   y_step;
   int   x_next_bord;
   float   x_step;
   int   x_col;


   //look for horisontal intersection:
   x_col = game->ray_x / CELL_SIZE;
   if (ray_x_dir == 1)
     x_col += 1;
   else
      x_col += 1;
   x_next_bord = x_col * CELL_SIZE;
   x_step = fabsf(x_next_bord - game->ray_x);
   //TODO: change first_ray_angle to the actual ray angle
   y_step = fabs(x_step * tan(game->first_ray_angle));
   game->ray_x = game->ray_x + ray_x_dir * x_step;
   game->ray_y = game->ray_y + ray_y_dir * y_step;
}

int  ft_check_hor_intersection(t_game_info   *game, int ray_y_dir)
{
   //check horisontal intersection:
   int col;
   int row;

   col = game->ray_x / CELL_SIZE;
   row = (game->ray_y + ray_y_dir) / CELL_SIZE;
   //printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
      return (1);
   else
      return (0);
}

int  ft_check_vert_intersection(t_game_info   *game, int ray_x_dir)
{
   //check vetical intersection:
   int col;
   int row;

   col = (game->ray_x + ray_x_dir) / CELL_SIZE;
   row = game->ray_y / CELL_SIZE;
   printf("ray_x %f\n", game->ray_x);
   printf("ray_y %f\n", game->ray_y);
   printf("col: %d\n", col);
   printf("col: %d\n", row);
    printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
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
   printf("ray_x_dir %d\n", *ray_x_dir);
   printf("ray_y_dir %d\n", *ray_y_dir);
}

int   ft_len_def(t_game_info *game)
{
  int correct_len;
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
   float   correct_len;

   //work with horizontal intersections
   hit_wall = 0;
   ft_ray_dir_def(game, &ray_x_dir, &ray_y_dir);
   printf("ray x dir: %d, ray y dir: %d\n", ray_x_dir, ray_y_dir);
   printf("hit wall: %d\n", hit_wall);

   while (!hit_wall)
     {
      write(1, "__________\n", 11);
         ft_first_hor_step(game, ray_x_dir, ray_y_dir);
//         ft_first_vert_step(game, ray_x_dir, ray_y_dir);
        if (ft_check_hor_intersection(game, ray_y_dir))
           hit_wall = 1;
         //  if (ft_check_vert_intersection(game, ray_x_dir))
         //    hit_wall = 1;
      write(1, "__________\n", 11);
     }
   correct_len = ft_len_def(game);
   printf("hit wall: %d\n", hit_wall);
   printf("correct_len: %f\n", correct_len);
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

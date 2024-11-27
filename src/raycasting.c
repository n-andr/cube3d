#include "../cube3d.h"

float  ft_hor_step(t_game_info *game, t_ray  *hor)
{
   float   x_step;
   int   y_next_bord;
   float   y_step;
   int   y_col;
   float hor_len;


   //look for horisontal intersection:
   y_col = hor->ray_y / CELL_SIZE;
   if (hor->ray_x_dir == 1)
     y_col += 1;
   else
      y_col += 1;
   y_next_bord = y_col * CELL_SIZE;
   y_step = fabsf(y_next_bord - hor->ray_y);
   //TODO: change first_ray_angle to the actual ray angle
   x_step = fabs(y_step / tan(game->first_ray_angle));
   hor->ray_y = hor->ray_y + hor->ray_y_dir * y_step;
   hor->ray_x = hor->ray_x + hor->ray_x_dir * x_step;
   hor_len = sqrt(x_step * x_step + y_step * y_step);
   printf("y_next_bord %d\n", y_next_bord);
   //printf("p_position_raw: %d\n", game->p_position_row);
   printf("first_ray_angle %f\n", game->first_ray_angle);
   printf("x_step %f\n", x_step);
   printf("y_step %f\n", y_step);
   return (hor_len);
}

float  ft_vert_step(t_game_info *game, t_ray *vert)
{
   int   x_next_bord;
   int   x_col;
   float vert_len;

   //look for horisontal intersection:
   x_col = vert->ray_x / CELL_SIZE;
   if (vert->ray_x_dir == 1)
     x_col += 1;
   else
      x_col += 1;
   x_next_bord = x_col * CELL_SIZE;
   vert->x_step = fabsf(x_next_bord - vert->ray_x);
   //TODO: change first_ray_angle to the actual ray angle
   vert->y_step = fabs(vert->x_step * tan(game->first_ray_angle));
   vert->ray_x = vert->ray_x + vert->ray_x_dir * vert->x_step;
   vert->ray_y = vert->ray_y + vert->ray_y_dir * vert->y_step;
   vert_len = sqrt(vert->x_step * vert->x_step + vert->y_step * vert->y_step);
   return (vert_len);
}

int  ft_check_hor_intersection(t_game_info   *game, t_ray *hor)
{
   //check horisontal intersection:
   int col;
   int row;

   col = hor->ray_x / CELL_SIZE;
   row = (hor->ray_y + hor->ray_y_dir) / CELL_SIZE;
   //printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
      return (1);
   else
      return (0);
}

int  ft_check_vert_intersection(t_game_info   *game, t_ray *vert)
{
   //check vetical intersection:
   int col;
   int row;

   col = (vert->ray_x + vert->ray_x_dir) / CELL_SIZE;
   row = vert->ray_y / CELL_SIZE;
   printf("ray_x %f\n", vert->ray_x);
   printf("ray_y %f\n", vert->ray_y);
   printf("col: %d\n", col);
   printf("col: %d\n", row);
    printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
      return (1);
   else
      return (0);
}

void ft_ray_dir_def(t_game_info *game, t_ray  *hor, t_ray *vert)
{
   if (game->first_ray_angle > 0 && game->first_ray_angle < M_PI)
   {
      hor->ray_y_dir = 1;
      vert->ray_y_dir = 1;
   }
   else
   {
      hor->ray_y_dir = -1;
      vert->ray_y_dir = -1;
   }
   if (game->first_ray_angle > M_PI / 2 && game->first_ray_angle < 3 * M_PI / 2)
   {
      hor->ray_x_dir = -1;
      vert->ray_x_dir = -1;
   }
   else
   {
      hor->ray_x_dir = 1;
      vert->ray_x_dir = 1;
   }
   printf("ray_x_dir %d\n", hor->ray_x_dir);
   printf("ray_y_dir %d\n", hor->ray_y_dir);
}

int   ft_len_def(t_game_info *game, t_ray *ray)
{
  int correct_len;
  float len;
  float del_x;
  float del_y;
  float angle;

   del_x = fabs(ray->ray_x - game->player.x);
   del_y = fabs(ray->ray_y - game->player.y);
   angle = game->player.p_angle - game->first_ray_angle;
   len = sqrt(del_x * del_x + del_y * del_y);
  //TODO: change the first ray angle to current angle
   correct_len = fabs(len * cos(angle));
   printf("del_x: %f, del_y: %f, angle: %f\n", del_x, del_y, angle);
   printf("len: %f\n", len);
   return (correct_len);
}

int   ft_find_intersections(t_game_info  *game)
{

   float   correct_len;
   t_ray   hor;
   t_ray   vert;

   ft_ray_dir_def(game, &hor, &vert);
   vert.len = 0;
   hor.len = 0;
   hor.ray_x = game->player.x;
   hor.ray_y = game->player.y;
   vert.ray_x = game->player.x;
   vert.ray_y = game->player.y;
   while (1)
     {
      vert.len += ft_vert_step(game, &vert);
        if (ft_check_vert_intersection(game, &vert))
            break ;
     }
   while (1)
      {
         hor.len += ft_hor_step(game, &hor);
         if (ft_check_hor_intersection(game, &hor))
            break ;
      }
   if (vert.len < hor.len)
      correct_len = ft_len_def(game, &vert);
   else
      correct_len = ft_len_def(game, &hor);
   printf("correct_len: %f\n", correct_len);
   return (correct_len);
}


   void  ft_raycasting(t_game_info	*game)
{
   printf("pi: %f\n", M_PI);
   printf("angle: %f\n",game->player.p_angle);
   printf("p_cell_x: %d\n",game->player.x);
   printf("p_cell_y: %d\n",game->player.y);
   ft_find_intersections(game);
}

#include "../cube3d.h"

float  ft_hor_step(t_game_info *game, t_ray  *hor)
{
   int   y_next_bord;
   int   y_col;
   float hor_len;
   float final_angle;

   //look for horisontal intersection:
   y_col = hor->ray_y / CELL_SIZE;
   if (hor->ray_x_dir == 1)
     y_col += 1;
   else
      y_col += 1;
   y_next_bord = y_col * CELL_SIZE;
   hor->y_step = fabsf(y_next_bord - hor->ray_y);
   final_angle = fabsf(hor->angle - game->player.p_angle);
  //printf("FINAL ANGLE %f\n", final_angle);
   if ((game->player.p_angle > M_PI / 4 && game->player.p_angle < 3 * M_PI / 4)
      || (game->player.p_angle > 5 * M_PI / 4 && game->player.p_angle < 7 * M_PI / 4))
      hor->x_step = hor->y_step * tan(final_angle);
   else
      hor->x_step = hor->y_step / tan(final_angle);
   hor->ray_y = hor->ray_y + hor->ray_y_dir * hor->y_step;
   if (final_angle)
      hor->ray_x = hor->ray_x + hor->ray_x_dir * hor->x_step;
   hor_len = sqrt(hor->x_step * hor->x_step + hor->y_step * hor->y_step);
  // printf("y_next_bord %d\n", y_next_bord);
   //printf("p_position_raw: %d\n", game->p_position_row);
  // printf("ray_angle %f\n", hor->angle);
  // printf("x_step %f\n", hor->x_step);
  // printf("y_step %f\n", hor->y_step);
  // printf("hor_len %f\n", hor_len);
   return (hor_len);
}

float  ft_vert_step(t_game_info *game, t_ray *vert)
{
   int   x_next_bord;
   int   x_col;
   float vert_len;
   float final_angle;

   //look for horisontal intersection:
   x_col = vert->ray_x / CELL_SIZE;
   if (vert->ray_x_dir == 1)
     x_col += 1;
   else
      x_col += 1;
   x_next_bord = x_col * CELL_SIZE;
   vert->x_step = fabsf(x_next_bord - vert->ray_x);
   //TODO: change first_ray_angle to the actual ray angle
   //printf("vert: ray angle: %f\n", vert->angle);
   //printf("player angle: %f\n", game->player.p_angle);
   final_angle = fabsf(vert->angle - game->player.p_angle);
   if ((game->player.p_angle > M_PI / 4 && game->player.p_angle < 3 * M_PI / 4)
      || (game->player.p_angle > 5 * M_PI / 4 && game->player.p_angle < 7 * M_PI / 4))
      vert->y_step = vert->x_step / tan(final_angle);
   else
      vert->y_step = vert->x_step * tan(final_angle);
  // printf("final angle: %f\n", final_angle);
   vert->ray_x = vert->ray_x + vert->ray_x_dir * vert->x_step;
   if (final_angle)
      vert->ray_y = vert->ray_y + vert->ray_y_dir * vert->y_step;
  // printf("vert x_step: %f\n", vert->x_step);
  // printf("vert y_step: %f\n", vert->y_step);
   vert_len = sqrt(vert->x_step * vert->x_step + vert->y_step * vert->y_step);
   return (vert_len);
}

int  ft_check_hor_intersection(t_game_info   *game, t_ray *hor)
{
   int col;
   int row;

  // printf("hor_len %d\n", hor->len);
  // write(1, "lol\n", 4);
  // printf("diff angle: %f\n", fabs(hor->angle - game->player.p_angle));
  // write(1, "lol\n", 4);
   col = hor->ray_x / CELL_SIZE;
   row = (hor->ray_y + hor->ray_y_dir) / CELL_SIZE;
  // printf("ray_x %f\n", hor->ray_x);
  // printf("ray_y %f\n", hor->ray_y);
  // printf("col: %d\n", col);
   // printf("row: %d\n", row);
   // printf("hor angle: %f\n", hor->angle);
   // printf("game->player.p_angle %f\n", game->player.p_angle);
   // printf("fabs(hor->angle - game->player.p_angle) %f\n", fabs(hor->angle - game->player.p_angle));
   // printf("game->epsilon: %f\n", game->epsilon);
   if (col >= game->columns || row >= game->rows || (col < 0 || row < 0))
      //|| hor->angle == 0 || hor->angle == M_PI)
   {
    //  write (1, "caught\n", 7);
      return (-1);
   }
 //  printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
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
   // printf("col: %d\n", col);
   // printf("row: %d\n", row);
   // printf("vert: ray_x %f\n", vert->ray_x);
   // printf("vert: ray_y %f\n", vert->ray_y);
   // printf("rows: %d\n", game->rows);
    if ((col >= game->columns || row >= game->rows) || (col < 0 || row < 0))
       return (-1);
   //printf("game->map[%d][%d]: %d\n", col, row, game->map[row][col]);
   if (game->map[row][col] == '1')
   {
      //write(1, "pup\n", 4);
      return (1);
   }
   return (0);
}

void ft_ray_dir_def(t_ray  *hor, t_ray *vert)
{
   if ((hor->angle > 0 && hor->angle < M_PI) || hor->angle > 2 * M_PI)
   {
      hor->ray_y_dir = 1;
      vert->ray_y_dir = 1;
   }
   else
   {
      hor->ray_y_dir = -1;
      vert->ray_y_dir = -1;
   }
   if (hor->angle > M_PI / 2 && hor->angle < 3 * M_PI / 2)
   {
      hor->ray_x_dir = -1;
      vert->ray_x_dir = -1;
   }
   else
   {
      hor->ray_x_dir = 1;
      vert->ray_x_dir = 1;
   }
 //  printf("ray_x_dir %d\n", hor->ray_x_dir);
  // printf("ray_y_dir %d\n", hor->ray_y_dir);
}

int   ft_len_def(t_game_info *game, t_ray *ray)
{
  int correct_len;
  float len;
  float del_x;
  float del_y;
  float angle;

   del_x = fabs(ray->ray_x - game->player.x);
   // printf("ray_x ff: %f\n", ray->ray_x);
   // printf("player ff: %d\n", game->player.x);
   del_y = fabs(ray->ray_y - game->player.y);
   angle = game->player.p_angle - ray->angle;
   len = sqrt(del_x * del_x + del_y * del_y);
   correct_len = round(fabs(len * cos(angle)));
   // printf("del_x: %f, del_y: %f, angle: %f\n", del_x, del_y, angle);
   // printf("len: %f\n", len);
   return (correct_len);
}

int   ft_hor_vert_intersec_def(t_ray ray)
{
   printf("ray.angle: %f\n", ray.angle);
   if (((ray.angle > 5 * M_PI / 4) && (ray.angle < 7 * M_PI / 4))
         || ((ray.angle > M_PI / 4) && (ray.angle < 3 * M_PI / 4)))
         return (1);
   else
         return (0);
}

int   ft_find_intersections(t_game_info  *game, int i, int *hit_hor_wall)
{

   float   correct_len;
   t_ray   hor;
   t_ray   vert;
   float   delta_angle;
   int     intersection;

   delta_angle = (game->player.fov_angle * i) / S_W;
   hor.angle = game->first_ray_angle + delta_angle;
   vert.angle = hor.angle;
   vert.len = 0;
   hor.len = 0;
   hor.ray_x = game->player.x;
   hor.ray_y = game->player.y;
   vert.ray_x = game->player.x;
   vert.ray_y = game->player.y;
   ft_ray_dir_def(&hor, &vert);
  // printf("fov angle: %f\n", game->player.fov_angle);
  // printf("delta angle: %f\n", delta_angle);
   //printf("current angle: %f\n", hor.angle);
   while (1)
      {
         hor.len += round(ft_hor_step(game, &hor));
         intersection = ft_check_hor_intersection(game, &hor);
         if (intersection)
         {
       //  write(1, "_______________\n", 16);
        // printf("hor intersection: %d\n", hor.len);
       //  write(1, "_______________\n", 16);
            break ;
         }
      }
   if (intersection == -1 || hor.len < 0)
         hor.len = INT_MAX;
   while (1)
     {
      vert.len += round(ft_vert_step(game, &vert));
     // write(1, "lel\n", 4);
      printf("i: %d\n", i);
      intersection = ft_check_vert_intersection(game, &vert);
        if (intersection)
        {
      //  write(1, "_______________\n", 16);
       //  printf("vert intersection: %d\n", vert.len);
       //  write(1, "_______________\n", 16);
            break ;
        }
     }
     if (intersection == -1 || vert.len < 0)
         vert.len = INT_MAX;
   //printf("hor.len: %d\n", hor.len);
   //printf("vert.len: %d\n", vert.len);
   *hit_hor_wall = 0;
   if (vert.len < hor.len)
   {
      //printf("ver.ray_x %f\n", vert.ray_x);
      //printf("ver.ray_y %f\n", vert.ray_y);
      correct_len = ft_len_def(game, &vert);
   }
   else if (vert.len > hor.len)
   {
      //printf("ver.ray_x %f\n", vert.ray_x);
      //printf("ver.ray_y %f\n", vert.ray_y);
      correct_len = ft_len_def(game, &hor);
      *hit_hor_wall = 1;
   }
   else
   {
      correct_len = ft_len_def(game, &hor);
      *hit_hor_wall = ft_hor_vert_intersec_def(vert);
      printf("FOUND ==\n");
   }
   //printf("correct_len: %f\n", correct_len);
   // if (vert.len == hor.len)
   // {
   //    printf("hit_hor: %d\n", *hit_hor_wall);
   //    exit(228);
   // }
   return (correct_len);
}


void  ft_print_lines_data(t_line *lines, int num)
{
   int i;

   i = 0;
   while (i < num)
   {
      //printf("hight[%d]: %d\n", i, lines[i].high);
      //printf("x[%d]: %d\n", i, lines[i].x);
      //printf("y1[%d]: %d\n", i, lines[i].y1);
      //printf("y2[%d]: %d\n", i, lines[i].y2);
      //printf("hight[%d]: %d\n", i, lines[i].high);
      printf("correct_len[%d]: %d\n", i, lines[i].correct_len);
      i++;
   }
}

   void  ft_raycasting(t_game_info	*game)
{
   int   i;
   t_line *lines;
   int   hit_hor_wall;


   lines = (t_line *)malloc(S_W * sizeof(t_line));
   // printf("pi: %f\n", M_PI);
   // printf("angle: %f\n",game->player.p_angle);
   // printf("p_cell_x: %d\n",game->player.x);
   // printf("p_cell_y: %d\n",game->player.y);

     i = 0;
   while (i < S_W)
   {
      lines[i].correct_len = ft_find_intersections(game, i, &hit_hor_wall);
      //printf("cor len: %d\n", correct_len);
      //lines[i].high = ((S_H / 2) * CELL_SIZE) / lines[i].correct_len;
      lines[i].high = S_H * CELL_SIZE / lines[i].correct_len;
      lines[i].x = i;
      lines[i].y1 = (S_H - lines[i].high) / 2;
      if (lines[i].y1 < 0)
           lines[i].y1 = 0;
      lines[i].y2 = S_H - lines[i].y1;
      if (lines[i].y2 > S_H)
           lines[i].y2 = S_H;
      lines[i].color = 16744703;
      if (hit_hor_wall)
         lines[i].color -= 10000;
      printf("hit hor: %d\n", hit_hor_wall);
      if (i == 1034)
         break;
      i++;
   }
   //ft_print_lines_data(lines, 129);
   ft_game_draw(game, lines);
}

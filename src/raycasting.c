#include "../cube3d.h"

float  ft_hor_step(t_game_info *game, t_ray  *hor)
{
   float   y_next_bord;
   int     hor_len;
   float   final_angle;

   //look for horisontal intersection:
   printf("current hor->row = %d\n", hor->row);
   hor->row = hor->row + hor->ray_y_dir;
   if (hor->ray_y_dir == 1)
   		y_next_bord = hor->row * CELL_SIZE;
   else
     	y_next_bord = (hor->row + 1) * CELL_SIZE;
   printf("hor->ray_y_dir = %d\n", hor->ray_y_dir);
   printf("next hor->row = %d\n", hor->row);
   printf("player.y = %d\n", game->player.y);
   printf("hor->ray_y = %f\n", hor->ray_y);
   printf("y_next_bord = %f\n", y_next_bord);
   hor->y_step = fabs(y_next_bord - hor->ray_y);
   printf("hor_y_step = %f\n", hor->y_step);
   printf("hor->angle %f\n", hor->angle);
   printf("game->player.p_angle %f\n", game->player.p_angle);
   //final_angle = fabsf(hor->angle - game->player.p_angle);
   final_angle = fabsf(game->first_ray_angle + game->delt_angle);
  printf("FINAL ANGLE %f\n", final_angle);
   if ((game->player.p_angle > M_PI / 4 && game->player.p_angle < 3 * M_PI / 4)
      || (game->player.p_angle > 5 * M_PI / 4 && game->player.p_angle < 7 * M_PI / 4))
      hor->x_step = hor->y_step * tan(final_angle);
   else
      hor->x_step = hor->y_step / tan(final_angle);
   printf("hor_x_step = %f\n", hor->x_step);
   hor->ray_y = y_next_bord;
   if (final_angle)
      hor->ray_x = hor->ray_x + hor->ray_x_dir * hor->x_step;
   hor->col = (hor->ray_x + 0.1 * hor->ray_x_dir) / CELL_SIZE;
   hor_len = round(sqrt(hor->x_step * hor->x_step + hor->y_step * hor->y_step));
   printf("next hor->ray_x = %f\n", hor->ray_x);
   printf("next hor->ray_y = %f\n", hor->ray_y);
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
   int vert_len;
   float final_angle;
   float   x_next_bord;

   //look for horisontal intersection:
   vert->col = vert->col + vert->ray_x_dir;
   if (vert->ray_x_dir == 1)
   		x_next_bord = vert->col * CELL_SIZE;
   else
     	x_next_bord = (vert->col + 1) * CELL_SIZE;
   vert->x_step = fabsf(x_next_bord - vert->ray_x);
   printf("player.x = %d\n", game->player.x);
   printf("vert->ray_x = %f\n", vert->ray_x);
   printf("x_next_bord = %f\n", x_next_bord);
   printf("vert_x_step = %f\n", vert->x_step);
   //printf("vert: ray angle: %f\n", vert->angle);
   //printf("player angle: %f\n", game->player.p_angle);
   final_angle = fabs(vert->angle - game->player.p_angle);
   if ((game->player.p_angle > M_PI / 4 && game->player.p_angle < 3 * M_PI / 4)
      || (game->player.p_angle > 5 * M_PI / 4 && game->player.p_angle < 7 * M_PI / 4))
      vert->y_step = vert->x_step / tan(final_angle);
   else
      vert->y_step = vert->x_step * tan(final_angle);
   printf("y_step = %f\n", vert->y_step);
  // printf("final angle: %f\n", final_angle);
   vert->ray_x = x_next_bord;
   printf("next vert->ray_x = %f\n", vert->ray_x);
   if (final_angle)
      vert->ray_y = vert->ray_y + vert->ray_y_dir * vert->y_step;
   vert->row = ((vert->ray_y + 0.1 * vert->ray_y_dir) / CELL_SIZE);
  printf("next vert->ray_y = %f\n", vert->ray_y);
  // printf("vert y_step: %f\n", vert->y_step);
  // printf("vert x_step: %f\n", vert->x_step);
   vert_len = round(sqrt(vert->x_step * vert->x_step + vert->y_step * vert->y_step));
   return (vert_len);
}

int  ft_check_intersection(t_game_info   *game, t_ray *ray)
{
    printf("ray_x %f\n", ray->ray_x);
    printf("ray_y %f\n", ray->ray_y);
    printf("col: %d\n", ray->col);
    printf("row: %d\n", ray->row);
   // printf("rows: %d\n", game->rows);
    if ((ray->col >= game->columns || ray->row >= game->rows) || (ray->col < 0 || ray->row < 0))
       return (-1);
   printf("game->map[%d][%d]: %d\n", ray->col, ray->row, game->map[ray->row][ray->col]);
   if (game->map[ray->row][ray->col] == '1')
      return (1);
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

void   ft_hor_vert_intersec_def(t_line *lines, int i)
{
   if (i)
      lines[i].hit_hor_wall = lines[i - 1].hit_hor_wall;
}

int   ft_find_intersections(t_game_info  *game, int i, t_line *lines)
{
   int   correct_len;
   t_ray   hor;
   t_ray   vert;
   float   delta_angle;
   int     intersection;

   delta_angle = (game->player.fov_angle * i) / S_W;
   hor.angle = game->first_ray_angle + delta_angle;
   printf("i: %d\n", i);
   printf("delta_angle: %f\n", delta_angle);
   vert.angle = hor.angle;
   vert.len = 0;
   hor.len = 0;
   hor.ray_x = game->player.x;
   hor.ray_y = game->player.y;
   vert.ray_x = game->player.x;
   vert.ray_y = game->player.y;
   vert.col = game->player.p_position_col;
   vert.row = game->player.p_position_row;
   hor.col = game->player.p_position_col;
   hor.row = game->player.p_position_row;
   ft_ray_dir_def(&hor, &vert);
   printf("game->player.p_position_row = %d\n", game->player.p_position_row);
   printf("game->player.p_position_col = %d\n", game->player.p_position_col);
  // printf("fov angle: %f\n", game->player.fov_angle);
  // printf("delta angle: %f\n", delta_angle);
   //printf("current angle: %f\n", hor.angle);
   while (1)
      {
         hor.len += ft_hor_step(game, &hor);
         intersection = ft_check_intersection(game, &hor);
         if (intersection)
         {
         write(1, "_______________\n", 16);
         printf("hor intersection: %d\n", hor.len);
        write(1, "_______________\n", 16);
            break ;
         }
      }
   if (intersection == -1 || hor.len < 0)
         hor.len = INT_MAX;
   while (1)
     {
      vert.len += ft_vert_step(game, &vert);
      printf("i: %d\n", i);
      intersection = ft_check_intersection(game, &vert);
        if (intersection)
        {
        write(1, "_______________\n", 16);
         printf("vert intersection: %d\n", vert.len);
         write(1, "_______________\n", 16);
            break ;
        }
     }
     if (intersection == -1 || vert.len < 0)
         vert.len = INT_MAX;
   lines[i].hit_hor_wall = 0;
   printf("i: %d\n", i);
   printf("player.x_pos: %d\n", game->player.x);
   printf("player.y_pos: %d\n", game->player.y);
   printf("p_position_row: %d, p_position_col: %d \n", game->player.p_position_row,  game->player.p_position_col); //debug
   printf("x: %d, y: %d \n", game->player.x,  game->player.y);
   if (vert.len < hor.len)
   {
      printf("vert intersection chosen: %d\n", vert.len);
      printf("hor.len: %d\n", hor.len);
      correct_len = ft_len_def(game, &vert);
   }
   else if (vert.len > hor.len)
   {
      printf("hor intersection chosen: %d\n", hor.len);
      printf("vert.len: %d\n", vert.len);
      correct_len = ft_len_def(game, &hor);
      lines[i].hit_hor_wall = 1;
   }
   else
   {
      correct_len = ft_len_def(game, &hor);
      ft_hor_vert_intersec_def(lines, i);
      printf("ANGLE FOUND!!\n");
   }
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
  // int   hit_hor_wall;


   lines = (t_line *)malloc(S_W * sizeof(t_line));
   // printf("pi: %f\n", M_PI);
   // printf("angle: %f\n",game->player.p_angle);
   // printf("p_cell_x: %d\n",game->player.x);
   // printf("p_cell_y: %d\n",game->player.y);

     i = 0;
     i = 640;
   //game->player.x = game->player.x - 16; // move player for debugging
   //while (i < S_W)
   //{
      lines[i].correct_len = ft_find_intersections(game, i, lines);
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
      if (lines[i].hit_hor_wall)
         lines[i].color -= 10000;
      //printf("hit hor: %d\n", lines[i].hit_hor_wall);
      // if (i == 640)
      //    break;
      //i++;
   //}
   game->lines = lines;
   //ft_print_lines_data(lines, 129);
}

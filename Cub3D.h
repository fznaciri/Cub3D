/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnaciri- <fnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:22:55 by fnaciri-          #+#    #+#             */
/*   Updated: 2020/02/10 18:48:22 by fnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
# define FALSE 0
# define TRUE 1
# define MAP_ROWS 14
# define MAP_COL  29
# define TILE_SIZE 64
# define MINI_MAP_SCALE 0.2
# define WIN_WIDTH (MAP_COL * TILE_SIZE)
# define WIN_HEIGHT (MAP_ROWS * TILE_SIZE)
# define FOV_ANGLE (60 * (M_PI / 180))
# define WALL_WIDTH 1
# define NUM_RAYS WIN_WIDTH // 928
# define EVENT_KEYDOWN 2
# define EVENT_KEYUP 3
# define EVENT_EXIT 17
# define MAX_INT 2147483647

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;


typedef struct s_player{
    float     x;
    float     y;
    int     width;
    int     height;
    int     walk_direction; // front or back
    int     turn_direction; // left or right
    float   rotation_angle;
    int     player_speed;
    float   rotation_speed;
}               t_player;

typedef struct s_rays{
    float   ray_angle;
    float   wall_hitx;
    float   wall_hity;
    float   distance;
    int     wall_hitcontent;
    int     vertical_hit;
    int     facing_down;
    int     facing_up;
    int     facing_right;
    int     facing_left;
}               t_rays;

int     initialize_window();
int     destroy_window();
void    setup();
int     key_down(int key);
int     key_up(int key);
void    process_input();
int     is_wall_at(int x, int y);
void    move_player();
float   normalize_angle(float angle);
float   distance(float x1, float y1, float x2, float y2);
void    cast_ray(float angle, int id);
void    cast_allrays();
void    update();
void    rect(int x, int y, int width, int height, int color);
void    line(int x, int y, float alpha, int d, int color);
void    render_player();
void    render_rays();
void    render_map();
void    render();
int     main_loop();

#endif
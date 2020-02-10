/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnaciri- <fnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:20:02 by fnaciri-          #+#    #+#             */
/*   Updated: 2020/02/10 12:57:10 by fnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void *mlx_ptr;

void *win_ptr;

t_data  img;

int isgamerunning = FALSE;

t_player g_player;

t_rays  g_rays[NUM_RAYS];

int     map[14][29] = {
        {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1},
        {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
        {1 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,1},
        {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1}
    };

int    initialize_window()
{
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
     {
        write(2, "ERROR INITIALIZING THE SERVER.\n", 31);
        return FALSE;
     }
    win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!win_ptr)
    {
        write(2, "ERROR CREATING THE WINDOW.\n", 27);
        return FALSE;
    }
    img.img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    return TRUE;
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int destroy_window()
{
    mlx_clear_window(mlx_ptr, win_ptr);
    mlx_destroy_window(mlx_ptr, win_ptr);
    exit(0);
    return 0;
}

void setup()
{
    g_player.x = WIN_WIDTH / 2;
    g_player.y = WIN_HEIGHT / 2;
    g_player.width = 2;
    g_player.height = 2;
    g_player.turn_direction = 0;
    g_player.walk_direction = 0;
    g_player.rotation_angle = M_PI / 4;
    g_player.player_speed = 20;
    g_player.rotation_speed = 10 * (M_PI / 180);
}

int key_down(int key, void *param)
{
    if (key == 53)
    {
        isgamerunning = FALSE;
        destroy_window();
    }
    if (key == 123) // left
         g_player.turn_direction = -1;
    if (key == 124) // right
         g_player.turn_direction = 1;
    if (key == 13) // up w
         g_player.walk_direction = 1;
    if (key == 1) // down s
         g_player.walk_direction = -1;
    if (key == 0) // turn left and walk a
    {
         g_player.walk_direction = 1;
         g_player.turn_direction = -1;
    }  
    if (key == 2) // turn right and walk d
    {
         g_player.walk_direction = 1;
         g_player.turn_direction = 1;
    }
    return 0;
}

int key_up(int key, void *param)
{
    if (key == 123 || key == 124) // left
         g_player.turn_direction = 0;
    if (key == 13 || key == 1) // up w
         g_player.walk_direction = 0;
    if (key == 0 || key == 2) // turn left and walk a
    {
         g_player.walk_direction = 0;
         g_player.turn_direction = 0;
    }  
    return 0;
}

void process_input()
{
    mlx_hook(win_ptr, EVENT_KEYDOWN, 0, key_down, (void*)0);
    mlx_hook(win_ptr, EVENT_KEYUP, 0, key_up, (void*)0);
    mlx_hook(win_ptr, EVENT_EXIT, 0, destroy_window, (void*)0);
}

int     is_wall_at(int x, int y)
{
    int index_x;
    int index_y;
    
    if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
        return TRUE;
    index_x = floor(x / TILE_SIZE);
    index_y = floor(y / TILE_SIZE);
    return (map[index_y][index_x] == 1 ? 1 : 0);
}

void move_player()
{
    float move_step;
    int new_playerx;
    int new_playery;
    
    move_step = g_player.walk_direction * g_player.player_speed;
    g_player.rotation_angle += g_player.turn_direction * g_player.rotation_speed;
    new_playerx = floor(g_player.x + move_step * cos(g_player.rotation_angle));
    new_playery = floor(g_player.y + move_step * sin(g_player.rotation_angle)); 
    if (!is_wall_at(new_playerx, new_playery))
    {
        g_player.x = new_playerx;
        g_player.y = new_playery; 
    }
}

 float normalize_angle(float angle)
{
    angle = remainderf(angle, 2 * M_PI);
    if (angle < 0)
         angle += 2 * M_PI; 
    return (angle);
}

float distance(float x1, float y1, float x2, float y2)
{
    return (hypotf((x2 - x1), (y2 - y1)));
}

void cast_ray(float angle, int id)
{
    float xstep;
    float ystep;
    float xintercept; // coordinate of the first intersection
    float yintercept;
    float next_horzx;
    float next_horzy;
    int horz_hit = FALSE;
    float horz_wall_hitx = 0;
    float horz_wall_hity = 0;
    int horz_wall_content = 0;
    float horz_distance;
    float vert_distance;
    
    angle = normalize_angle(angle);
    
    int facing_down = ((angle > 0 && angle < M_PI)? 1 : 0);
    int facing_up = !facing_down;
    
    int facing_right = ((angle < M_PI * 0.5 || angle > 1.5 * M_PI) ? 1 : 0);    
    int facing_left = !facing_right;
    
    /////////////////////////////
    // horizontal intersection //
    ////////////////////////////
    
    ystep = TILE_SIZE;
    ystep *= (facing_down ? 1 : -1);
    
    xstep = ystep / tan(angle);
   // xstep *= ((facing_right && xstep < 0) ? -1 : 1);
   // xstep *= ((facing_left && xstep > 0) ? -1 : 1);
    
    
    yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += (facing_down ? TILE_SIZE : 0);
    yintercept += (facing_up ? -1 : 0); // make it part of the bloc above the line 
    xintercept = g_player.x + ((yintercept - g_player.y) / tan(angle));
    
    next_horzx = xintercept;
    next_horzy = yintercept;
    
    while ((next_horzx > 0 && next_horzx < WIN_WIDTH) && (next_horzy > 0 && next_horzy < WIN_HEIGHT))
    {
        if (is_wall_at(next_horzx, next_horzy))
        {
            horz_hit = TRUE;
            horz_wall_hitx = next_horzx;
            horz_wall_hity = next_horzy;
            horz_wall_content = map[(int)floor(next_horzy / TILE_SIZE)][(int)floor(next_horzx / TILE_SIZE)];
            break;
        }
        else
        {
            next_horzx += xstep;
            next_horzy += ystep;
        }
    }

    ///////////////////////////////////////////////
    //////////// vertical intersection  ///////////
    ///////////////////////////////////////////////

    float next_vertx;
    float next_verty;
    int vert_hit = FALSE;
    float vert_wall_hitx = 0;
    float vert_wall_hity = 0;
    int vert_wall_content = 0;
    
    xstep = TILE_SIZE;
    xstep *= (facing_left ? -1 : 1);
    
    ystep = xstep * tan(angle);
    //ystep *= ((facing_up && ystep > 0) ? -1 : 1);
   // ystep *= ((facing_down && ystep < 0) ? -1 : 1);
    
    
    xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += (facing_right ? TILE_SIZE : 0);
    xintercept += (facing_left ? -1 : 0);
    yintercept = g_player.y + ((xintercept - g_player.x) * tan(angle));
    
    next_vertx = xintercept;
    next_verty = yintercept;
    
    while ((next_vertx > 0 && next_vertx < WIN_WIDTH) && (next_verty > 0 && next_verty < WIN_HEIGHT))
    {
        if (is_wall_at(next_vertx, next_verty))
        {
            vert_hit = TRUE;
            vert_wall_hitx = next_vertx;
            vert_wall_hity = next_verty;
            vert_wall_content = map[(int)floor(next_verty / TILE_SIZE)][(int)floor(next_vertx / TILE_SIZE)];
            break;
        }
        else
        {
            next_vertx += xstep;
            next_verty += ystep;
        }
    }
    horz_distance = horz_hit ? distance(g_player.x, g_player.y, horz_wall_hitx, horz_wall_hity) : MAX_INT;
    vert_distance = vert_hit ? distance(g_player.x, g_player.y, vert_wall_hitx, vert_wall_hity) : MAX_INT;
    if (vert_distance < horz_distance)
    {
        g_rays[id].distance = vert_distance;
        g_rays[id].wall_hitx = vert_wall_hitx;
        g_rays[id].wall_hity = vert_wall_hity;
        g_rays[id].wall_hitcontent = vert_wall_content;
        g_rays[id].vertical_hit = TRUE;
    }
    else
    {
        g_rays[id].distance = horz_distance;
        g_rays[id].wall_hitx = horz_wall_hitx;
        g_rays[id].wall_hity = horz_wall_hity;
        g_rays[id].wall_hitcontent = horz_wall_content;
        g_rays[id].vertical_hit = FALSE;
    }
    g_rays[id].ray_angle = angle;
    g_rays[id].facing_down = facing_down;
    g_rays[id].facing_up = facing_up;
    g_rays[id].facing_right = facing_right;
    g_rays[id].facing_left = facing_left;
}

void cast_allrays()
{
    int id = 0;
    float ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
    while (id < NUM_RAYS)
    {
        cast_ray(ray_angle, id);
        ray_angle += FOV_ANGLE / NUM_RAYS;
        id++;
    }
}
    
void update()
{
   move_player();
   cast_allrays();
}

void    rect(int x, int y, int width, int height, int color)
{   
    int i = 0;
    int j = 0;
    int k = x;
    
    while(j < height)
    {
        i = 0;
        while(i < width)
        {
            my_mlx_pixel_put(&img, k++, y, color);
            i++;
        }
        k = x;
        y++;
        j++;
    }
}

void    line(int x, int y, float alpha, int d, int color)
{
    int i;
    int new_x;
    int new_y;
    i = 0;
    while (i < d)
    {
        new_x = x + cos(alpha) * i;
        new_y = y + sin(alpha) * i;
        my_mlx_pixel_put(&img, new_x, new_y, color);
         i++;
    }
}

void render_player()
{
    rect(MINI_MAP_SCALE * g_player.x, MINI_MAP_SCALE * g_player.y, MINI_MAP_SCALE * g_player.width, MINI_MAP_SCALE * g_player.height, 0x00FF00);
    line(MINI_MAP_SCALE * (g_player.x + (g_player.width / 2)), MINI_MAP_SCALE * (g_player.y + (g_player.height / 2)), g_player.rotation_angle, MINI_MAP_SCALE * 10, 0x00FF00);
}

void render_rays()
{
    int i = 0;

    while (i < NUM_RAYS)
    {
       line(MINI_MAP_SCALE * g_player.x, MINI_MAP_SCALE * g_player.y, g_rays[i].ray_angle, MINI_MAP_SCALE * g_rays[i].distance, 0x8FFF0000);
        i++;
    }
}

void render_map()
{
    int i = 0;
    int j = 0;
    int color;
    
    while(i < MAP_ROWS)
    {
        j = 0;
        while(j < MAP_COL)
        {
            if (map[i][j] == 1)
                color = 0;
            else
                color = 0xFFFFFF;
            rect(MINI_MAP_SCALE * j * TILE_SIZE, MINI_MAP_SCALE * i * TILE_SIZE, MINI_MAP_SCALE * TILE_SIZE, MINI_MAP_SCALE * TILE_SIZE, color);
            j++;
        }
        i++;               
    }
}

void render_3dwall()
{
    int i = 0;
    int wall_height;
    float correct_distance;
    
    while(i < NUM_RAYS)
    {
        correct_distance = g_rays[i].distance * cos(g_rays[i].ray_angle - g_player.rotation_angle);
        wall_height = (TILE_SIZE / correct_distance) * ((WIN_WIDTH / 2) / tan(FOV_ANGLE / 2));
        rect(i * WALL_WIDTH, ((WIN_HEIGHT / 2) - (wall_height / 2)), WALL_WIDTH, wall_height, 0xFFFFFF);
        i++;
    }
}

void render()
{
    render_3dwall();
    render_map();
    render_rays();
    render_player();
}

void clear_image()
{
    rect(0, 0, WIN_WIDTH, WIN_HEIGHT, 0x000000);
}

int main_loop()
{
    update(); 
   
    render();
    mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
    clear_image();
    return 0;
}

int main()
{
    isgamerunning = initialize_window();
    setup();
    process_input();
    mlx_loop_hook(mlx_ptr, main_loop, (void*)0);
    mlx_loop(mlx_ptr);
}

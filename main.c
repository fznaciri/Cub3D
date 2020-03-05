/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnaciri- <fnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:20:02 by fnaciri-          #+#    #+#             */
/*   Updated: 2020/03/05 19:35:55 by fnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"



int     map[14][29] = {
        {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1},
        {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
        {1 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
        {1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1},
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
    *((unsigned int*)dst) = color;
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
    g_player.rotation_angle = M_PI / 10;
    g_player.player_speed = 8;
    g_player.rotation_speed = 8 * (M_PI / 180);
}

int key_down(int key)
{
    if (key == 53)
    {
        isgamerunning = FALSE;
        destroy_window();
    }
    if (key == 123 || key == 0) // left
         g_player.turn_direction = -1;
    if (key == 124 || key == 2) // right
         g_player.turn_direction = 1;
    if (key == 13 || key == 126) // up w 
         g_player.walk_direction = 1;
    if (key == 1 || key == 125) // down s
         g_player.walk_direction = -1;
    // if (key == 0) // turn left and walk a
    // {
    //      g_player.walk_direction = 1;
    //      g_player.turn_direction = -1;
    // }  
    // if (key == 2) // turn right and walk d
    // {
    //      g_player.walk_direction = 1;
    //      g_player.turn_direction = 1;
    // }
    return 0;
}

int key_up(int key)
{
    if (key == 123 || key == 124 || key == 0 || key == 2) // turn
         g_player.turn_direction = 0;
    if (key == 13 || key == 1 || key == 126 || key == 125) // up w
         g_player.walk_direction = 0;
    // if (key == 0 || key == 2) // turn left and walk a
    // {
    //      g_player.walk_direction = 0;
    //      g_player.turn_direction = 0;
    // }  
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
    float new_playerx;
    float new_playery;
    
    move_step = g_player.walk_direction * g_player.player_speed;
    g_player.rotation_angle += g_player.turn_direction * g_player.rotation_speed;
    new_playerx = (g_player.x + move_step * cos(g_player.rotation_angle));
    new_playery = (g_player.y + move_step * sin(g_player.rotation_angle)); 
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
    line(MINI_MAP_SCALE * (g_player.x + (g_player.width / 2)), MINI_MAP_SCALE * (g_player.y + (g_player.height / 2)), g_player.rotation_angle, MINI_MAP_SCALE * 50, 0x00FF00);
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

int  get_text_color(t_text text, int x, int y)
{
    if (x >= 0 && x < text.width && y >= 0 && y < text.height)
    {
        return(*((unsigned int*)text.addr + (y * text.width + x)));
    }
    return 0;
}

void load_texture(t_text *text)
{
    text->text = mlx_xpm_file_to_image(mlx_ptr, text->path, &text->width, &text->height);
    text->addr = mlx_get_data_addr(text->text, &text->bits_per_pixel, &text->line_length, &text->endian);
}

void set_text()  
{
    int i = 0;
    path.no = "./texture/7.xpm";
    path.so = "./texture/23.xpm";
    path.we = "./texture/eagle.xpm";
    path.es = "./texture/nazi.xpm";
    path.s  = "./texture/barrel.xpm"; 

    while (i < 5)
    {
        text[i].width = 64;
        text[i].height = 64;
        i++;
    }
    text[NORTH].path = path.no;
    text[SOUTH].path = path.so;
    text[WEST].path = path.we;
    text[EAST].path = path.es;
    text[SPRITE].path = path.s;


    load_texture(&text[NORTH]);
    load_texture(&text[SOUTH]);
    load_texture(&text[WEST]);
    load_texture(&text[EAST]);
    load_texture(&text[SPRITE]);
}


int texture(int i)
{
    // if(!g_rays[i].vertical_hit && g_rays[i].facing_up)
    //     return NORTH;
    // else if (!g_rays[i].vertical_hit && g_rays[i].facing_down)
    //     return SOUTH;
    // if (g_rays[i].vertical_hit && g_rays[i].facing_right)
    //     return WEST;
    // else if (g_rays[i].vertical_hit && g_rays[i].facing_left) 
    //     return EAST;
    if(!is_wall_at(g_rays[i].wall_hitx, g_rays[i].wall_hity - 1))
        return NORTH;
    else if (!is_wall_at(g_rays[i].wall_hitx, g_rays[i].wall_hity + 1))
        return SOUTH;
    if (!is_wall_at(g_rays[i].wall_hitx - 1, g_rays[i].wall_hity))
        return WEST;
    else if (!is_wall_at(g_rays[i].wall_hitx + 1, g_rays[i].wall_hity))
        return EAST;
    return 0;
}

// void    set_text()
// {
//     text.path = "./texture/wall_1.xpm";
//     text.width = 64;
//     text.height = 64;
// }

// void set_sp()
// {
//     int i;
//     int j;
   
//     i = 0;
//     while(i < MAP_ROWS)
//     {
//         j = 0;
//         while(j < MAP_COL)
//         {   
//             if(map[j][i] == 2)
//             {
//                 text[SPRITE].offset_x = j * TILE_SIZE  +  TILE_SIZE / 2;
//                 text[SPRITE].offset_y = i * TILE_SIZE + TILE_SIZE / 2;
//             }
//             j++;
//         }
//         i++;
//     }
// }

// void render_sprite()
// {
//     int size;
//     float d;
//     int sp_ystart;
//    // int sp_yend;
//     int sp_xstart;
//     //int sp_xend;
//     float angle;
//     unsigned int color;
//     int i;
//     int j;

//     set_sp();
//     d = distance(g_player.x, g_player.y, text[SPRITE].offset_x, text[SPRITE].offset_y);
//     angle = atan2(text[SPRITE].offset_y - g_player.y, text[SPRITE].offset_x - g_player.x); // angle between the player and the sprite
//     while (angle - g_player.rotation_angle > M_PI)
//         angle -= 2 * M_PI;
//     while (angle - g_player.rotation_angle < -M_PI)
//         angle += 2 * M_PI;
//     if (WIN_WIDTH < WIN_HEIGHT)
//         size = (WIN_HEIGHT / d) *  TILE_SIZE;
//     else
//         size = (WIN_WIDTH / d) *TILE_SIZE;
    
//     sp_ystart = (WIN_HEIGHT / 2) - (size / 2);
//     sp_ystart = sp_ystart < 0 ? 0 : sp_ystart;
//     //sp_yend = (WIN_HEIGHT / 2) + (size / 2);
//     //sp_yend = sp_yend > WIN_HEIGHT ? WIN_HEIGHT - 1 : sp_yend;
//     sp_xstart = (angle - g_player.rotation_angle)  * (WIN_WIDTH / FOV_ANGLE) + (WIN_WIDTH / 2 - size / 2);
//     sp_xstart = sp_xstart < 0 ? 0 : sp_xstart;
//     //sp_xend = (angle - g_player.rotation_angle)  * (WIN_WIDTH / FOV_ANGLE) + (WIN_WIDTH / 2 + size / 2);
//     //sp_xend = sp_xend > WIN_WIDTH ? WIN_WIDTH - 1 : sp_xend;

//     i = 0;
//     while(i < size)
//     {   
//         j = 0;
//         while(j < size)
//         {
//             color = get_text_color(text[SPRITE], i * text[SPRITE].width / size , j * (text[SPRITE].height/ size));
//             my_mlx_pixel_put(&img, sp_xstart + i, sp_ystart + j, color);
//             j++;
//         }
//         i++;
//     }

// }

void render_3dwall()
{
    int i = 0;
    int wall_height;
    float correct_distance;
    unsigned int color;
    int distance_from_top;
    int j;
    int wall_top;
    int wall_bot;
    int t;
    
    set_text();
    //load_texture();
    while(i < NUM_RAYS)
    {
        correct_distance = g_rays[i].distance * cos(g_rays[i].ray_angle - g_player.rotation_angle);
        wall_height = (TILE_SIZE / correct_distance) * ((WIN_WIDTH / 2) / (tan(FOV_ANGLE / 2)));
        wall_top = ((WIN_HEIGHT / 2) - (wall_height / 2));
        wall_top = wall_top < 0 ? 0 : wall_top;
        wall_bot = ((WIN_HEIGHT / 2) + (wall_height / 2));
        wall_bot = wall_bot > WIN_HEIGHT ? WIN_HEIGHT : wall_bot; 
       j = 0;
       t = texture(i);
       if (g_rays[i].vertical_hit)
           text[t].offset_x = (int)g_rays[i].wall_hity % TILE_SIZE;
       else
           text[t].offset_x = (int)g_rays[i].wall_hitx % TILE_SIZE;
        text[t].offset_x = text[t].offset_x < 0 ? 0 : text[t].offset_x;
       
        while(j < WIN_HEIGHT)
       {
            if (j < wall_top) // ceiling
                color = 0xCCFFFF;
            else if (j < wall_bot) // wall 
            {
                distance_from_top = j + (wall_height / 2) - (WIN_HEIGHT / 2);
                
                text[t].offset_y = distance_from_top * ((float)text[t].height / wall_height);
                text[t].offset_y = text[t].offset_y >= WIN_HEIGHT ? WIN_HEIGHT - 1 : text[t].offset_y;
                color = get_text_color(text[t], text[t].offset_x, text[t].offset_y);
            } 
            else if (j < WIN_HEIGHT) // floor
                color = 0x336600;
           my_mlx_pixel_put(&img, i, j, color);
           j++;
       }
       i++;
    }
}

void render()
{
    render_3dwall();
    render_map();
    render_rays();
    render_player();
   // render_sprite();
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

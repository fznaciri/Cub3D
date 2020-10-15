#include "Cub3D.h"

// t_sprite sp[NUM_SPRITE];


// void load_sprite(t_sprite *sp)
// {
//     sp->sp = mlx_xpm_file_to_image(mlx_ptr, sp->path, &sp->width, &sp->height);
//     sp->addr = mlx_get_data_addr(sp->text, &sp->bits_per_pixel, &sp->line_length, &sp->endian);
// }

void set_sp()
{
    int i;
    int j;
 
    i = 0;
    while(i < MAP_ROWS)
    {
        j = 0;
        while(j < MAP_COL)
        {   
            if(map[j][i] == 2)
            {
                sp.x = j * TILE_SIZE + TILE_SIZE / 2;
                sp.y = i * TILE_SIZE + TILE_SIZE / 2;
                sp.distance = distance(g_player.x, g_player.y, sp.x, sp.y);
               
            }
            j++;
        }
        i++;
    }
}

// void sort_sprite() // sort sprite from far to close
// {
//     int i;
//     int j;
//     int tmp;

//     i = 0;
//     while(i < NUM_SPRITE)
//     {
//         while(j < NUM_SPRITE - i)
//         {
//             if(sp[j].distance < sp[j + 1].distance)
//             {
//                 tmp = sp[j];
//                 sp[j] = sp[j + 1];
//                 sp[j + 1] = tmp;

//             }
//             j++;
//         }
//         i++;
//     }
// }

void    render_sprite()
{
    int size;
    int sp_xs;
    int sp_ys;
    float angle;
    unsigned int color;
    int i;
    int j;
    i = -1;
    int ws;
    int hs;

    init_sprite(&ws,&hs);
    set_sp();
    angle = atan2f(sp.y - g_player.y, sp.x - g_player.x) - g_player.rotation_angle;
    angle = normalize_angle(angle);
    if (WIN_WIDTH < WIN_HEIGHT)    
        size = (WIN_HEIGHT / d) * TILE_SIZE;
    else
        size = (WIN_WIDTH / d) * TILE_SIZE;
    sp_ys = (WIN_HEIGHT / 2) - (size / 2);
    sp_ys = sp_ys < 0 ? 0 : sp_ys;
    sp_xs = angle * (WIN_WIDTH / FOV_ANGLE) + (WIN_WIDTH / 2 - size / 2);
    while(++i < size)
    {   
        j = 0;
        while(j < size)
        {
           color = *(unsigned int*)sp.addr + ((j * (hs / size)) * ws) + (i * (ws / size));

        }
        

    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


void	init_sprite(int *ws, int *hs)
{
	int a;

    path.s  = "./texture/barrel.xpm";
	sp.sp = mlx_xpm_file_to_image(mlx_ptr, paths.s, ws, hs);
	if (sp.sp == NULL)
	{
		write(2, "error", 5);
		exit(0);
	}
	sp.addr = (int *)mlx_get_data_addr(sp.sp, &a, &a, &a);
}


void	set_sp(void)
{
	int i;
	int j;
	
	i = 0;
	while (i < MAP_ROWS)
	{
		j = 0;
		while (j < MAP_COL)
		{
			if (map[j][i] == 2)
			{
				sp.x = j * TILE_SIZE + TILE_SIZE / 2; // get to the center of the sprite
				sp.y = i * TILE_SIZE + TILE_SIZE / 2;
                sp.distance = distance(sp.x, sp.y, g_player.x, g_player.y);
			}
			j++;
		}
		i++;
	}
}

void	render_sprite(void)
{
	float	angle;
	float	size;
	float	x_start;
	float	y_start;
    int     ws;
    int     hs;
    unsigned int     color;
	int     i;
	int     j;
	
	init_sprite(&ws, &hs);
    set_sp();
    angle = atan2(sp.y - g_player.y, sp.x - g_player.x) - g_player.rotation_angle;
	// while (angle - (g_player.rotation_angle) > M_PI)
	// 	angle -= 2 * M_PI;
	// while (angle - (g_player.rotation_angle) < -M_PI)
	// 	angle += 2 * M_PI;
    angle = normalize_angle(angle);
	if (WIN_HEIGHT > WIN_WIDTH)
		size = (WIN_HEIGHT / sp.distance) * TILE_SIZE;
	else
		size = (WIN_WIDTH / sp.distance) * TILE_SIZE;
	y_start = (WIN_HEIGHT / 2) - (size / 2);
	x_start = (angle * WIN_WIDTH / FOV_ANGLE  + (WIN_WIDTH / 2 - size / 2);
	
	i = -1;
	while (++i < (int)size)
	{
		if ((int)x_start + i < 0 || (int)x_start + i > WIN_WIDTH)
			continue;
		if (sp.distance >= g_rays[(int)x_start + i].distance)
			continue;
		j = -1;
		while (++j < (int)size)
		{
			color = *(unsigned int*)sp.addr + (ws * (j * hs / (int)size) + (i * ws / (int)size));
			if (color != 0)
				if ((((int)x_start + i) >= 0 && ((int)x_start + i) < WIN_WIDTH) && (((int)y_start + j) >= 0 && ((int)y_start + j) < WIN_HEIGHT))
                    my_mlx_pixel_put(&img, (int)x_start + i, (int)y_start + j, color);
		}
	}
}




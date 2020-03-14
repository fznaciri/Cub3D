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
    //int k;

   // k = 0;
    i = 0;
    while(i < MAP_ROWS)
    {
        j = 0;
        while(j < MAP_COL)
        {   
            if(map[j][i] == 2)
            {
                text[SPRITE].offst_x = j * TILE_SIZE;
                text[SPRITE].offset_y = i * TILE_SIZE;
                // sp[k].distance = distance(g_player.x, g_player.y, sp[k].x, sp[k].y);
                // k++;
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
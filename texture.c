
#include "Cub3D.h"


void load_texture(t_text text, char *path)
{
    text.text = mlx_xpm_file_to_image(mlx_ptr, path, &text.width, &text.height);
    text.addr = mlx_get_data_addr(text.text, &text.bits_per_pixel, &text.line_length, &text.endian);
}

void texture()
{
    load_texture(text[NORTH], path.no);
    load_texture(text[SOUTH], path.so);
    load_texture(text[WEST], path.we);
    load_texture(text[EAST], path.es);
    
    
}

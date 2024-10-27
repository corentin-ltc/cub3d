#include "cub3d.h"

void	put_pixel(t_vector pixel, t_img img, int color)
{
	char	*img_pixel;
	int		offset;

	if (pixel.x < 0 || pixel.y < 0)
		return ;
	if (pixel.x >= WINDOW_WIDTH || pixel.y >= WINDOW_HEIGHT)
		return ;
	offset = (pixel.y * img.line_length + pixel.x * (img.bits_per_pixel / 8));
	img_pixel = img.addr + offset;
	*(unsigned int *)img_pixel = color;
}

void	put_minimap_pixel(t_vector pixel, int color, t_data *data)
{
	pixel.x = pixel.x - (data->player.pos.x * BLOCK_SIZE) + (MINIMAP_SIZE);
	pixel.y = pixel.y - (data->player.pos.y * BLOCK_SIZE) + (MINIMAP_SIZE);
	// if (get_distance(pos(pixel.x, pixel.y), pos(MINIMAP_X, MINIMAP_Y)) > BLOCK_SIZE * RENDER_DISTANCE)
	// 	return ;
	put_pixel(pixel, data->mlx.minimap, color);
}

void    put_block(t_data *data, t_vector cell)
{
    t_vector    pixel;
    t_vector    i;
    
    i.y = 1;
    while (i.y < BLOCK_SIZE)
    {
        i.x = 0;
        while (++i.x < BLOCK_SIZE)
        {
			pixel.x = (cell.x * BLOCK_SIZE) + i.x;
			pixel.y = (cell.y * BLOCK_SIZE) + i.y;
            if (data->map[cell.y][cell.x] == WALL)
                put_minimap_pixel(pixel, WALL_COLOR, data);
            else if (data->map[cell.y][cell.x] == FLOOR)
                put_minimap_pixel(pixel, FLOOR_COLOR, data);
        }
        i.y++;
    }
}

void	put_cube(t_pos center, int size, int color, t_data *data)
{
	int	x;
	int	y;

	y = -size / 2;
	while (y <= size / 2)
	{
		x = -size / 2;
		while (x <= size / 2)
		{
			put_minimap_pixel(vector(center.x + x, center.y + y), color, data);
			x++;
		}
		y++;
	}
}

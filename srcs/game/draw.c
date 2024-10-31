#include "cub3d.h"

void	put_pixel(t_vector pixel, t_img img, int color)
{
	char	*img_pixel;
	int		offset;

	if (pixel.x < 0 || pixel.y < 0)
		return ;
	if (pixel.x >= img.width || pixel.y >= img.height)
		return ;
	offset = (pixel.y * img.line_length + pixel.x * (img.bits_per_pixel / 8));
	img_pixel = img.addr + offset;
	*(unsigned int *)img_pixel = color;
}

void	put_minimap_pixel(t_vector pixel, int color, t_data *data)
{
	pixel.x = pixel.x - (data->player.pos.x * MINIMAP_BLOCK_SIZE) + (MINIMAP_SIZE);
	pixel.y = pixel.y - (data->player.pos.y * MINIMAP_BLOCK_SIZE) + (MINIMAP_SIZE);
	if (get_distance(pos(pixel.x, pixel.y), pos(MINIMAP_CENTER, MINIMAP_CENTER)) > MINIMAP_BLOCK_SIZE * RENDER_DISTANCE)
		return ;
	put_pixel(pixel, data->mlx.game, color);
}

void    put_block(t_data *data, t_vector cell)
{
    t_vector    pixel;
    t_vector    i;
    
    i.y = GRID;
    while (i.y < MINIMAP_BLOCK_SIZE)
    {
        i.x = GRID;
        while (i.x < MINIMAP_BLOCK_SIZE)
        {
			pixel.x = (cell.x * MINIMAP_BLOCK_SIZE) + i.x;
			pixel.y = (cell.y * MINIMAP_BLOCK_SIZE) + i.y;
            if (data->map[cell.y][cell.x] == WALL)
                put_minimap_pixel(pixel, WALL_COLOR, data);
            else if (data->map[cell.y][cell.x] == FLOOR)
                put_minimap_pixel(pixel, FLOOR_COLOR, data);
			i.x ++;
        }
        i.y++;
    }
}

void	put_cube(t_pos center, int size, int color, t_data *data)
{
	int	x;
	int	y;

	y = -size >> 1;
	while (y <= size >> 1)
	{
		x = -size >> 1;
		while (x <= size >> 1)
		{
			put_minimap_pixel(vector(center.x + x, center.y + y), color, data);
			x++;
		}
		y++;
	}
}

void	put_ray(t_ray ray, int color, t_data *data)
{
	int	i;
	
	i = 0;
	while (i < ray.distance * MINIMAP_BLOCK_SIZE && i < MINIMAP_SIZE)
	{
		ray.dir = pos(cos(ray.angle) * i, sin(ray.angle) * i);
		if (i && RAY_RATE != 0 && i % RAY_RATE == 0)
			put_minimap_pixel(vector(((ray.start.x * MINIMAP_BLOCK_SIZE) + ray.dir.x), ((ray.start.y * MINIMAP_BLOCK_SIZE) + ray.dir.y)), color, data);
		i++;
	}
}
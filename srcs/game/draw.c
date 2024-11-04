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

static void show_cursor(t_data *data, int color)
{
    t_pos    win_center;
    t_ray    line;

    win_center = pos(data->mlx.window_width / 2, data->mlx.window_height / 2);
    line.distance = CURSOR_LENGTH;
    put_pixel(vector(win_center.x, win_center.y), data->mlx.game, RED);
    line.angle = 0;
    line.start = pos(win_center.x + CURSOR_SPACE, win_center.y);
    put_ray(line, color, data, false);
    line.angle = PI * 0.5;
    line.start = pos(win_center.x, win_center.y + CURSOR_SPACE);
    put_ray(line, color, data, false);
    line.angle = PI;
    line.start = pos(win_center.x - CURSOR_SPACE, win_center.y);
    put_ray(line, color, data, false);
    line.angle = PI * 1.5;
    line.start = pos(win_center.x, win_center.y - CURSOR_SPACE);
    put_ray(line, color, data, false);
}

void    put_ray(t_ray ray, int color, t_data *data, bool minimap)
{
    int    i;
    
    if (minimap)
        ray.distance *= MINIMAP_BLOCK_SIZE;
    i = 0;
    while (i < ray.distance && (minimap == false || i < MINIMAP_SIZE))
    {
        ray.dir = pos(cos(ray.angle) * i, sin(ray.angle) * i);
        if (minimap == false)
        {
            put_pixel(vector((int)(ray.start.x + ray.dir.x), (int)(ray.start.y + ray.dir.y)), data->mlx.game, color);
            put_pixel(vector(450, 450), data->mlx.game, color);
        }
        else if (i && RAY_RATE != 0 && i % RAY_RATE == 0)
            put_minimap_pixel(vector(((ray.start.x * MINIMAP_BLOCK_SIZE) + ray.dir.x), ((ray.start.y * MINIMAP_BLOCK_SIZE) + ray.dir.y)), color, data);
        i++;
    }
}
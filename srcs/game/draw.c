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
	if (get_distance(pos(pixel.x, pixel.y), pos(MINIMAP_X, MINIMAP_Y)) > BLOCK_SIZE * RENDER_DISTANCE)
		return ;
	put_pixel(pixel, data->mlx.minimap, color);
}

void    put_block(t_data *data, t_vector cell)
{
    t_vector    pixel;
    t_vector    i;
    
    i.y = 0;
    while (i.y < BLOCK_SIZE)
    {
        i.x = -1;
        while (++i.x < BLOCK_SIZE)
        {
			pixel.x = (cell.x * BLOCK_SIZE) + i.x;
			pixel.y = (cell.y * BLOCK_SIZE) + i.y;
            if (i.x == 0 || i.y == 0)
                put_minimap_pixel(pixel, WHITE, data);
            else if (data->map[cell.y][cell.x] == WALL)
                put_minimap_pixel(pixel, WALL_COLOR, data);
            else if (data->map[cell.y][cell.x] == FLOOR)
                put_minimap_pixel(pixel, FLOOR_COLOR, data);
        }
        i.y++;
    }
}

void put_direction_arrow(t_data *data)
{
	t_pos player;
	t_pos arrow;
	t_pos new;
	double arrow_length;
	double t;
	int	i;

    player.x  = MINIMAP_SIZE;
    player.y  = MINIMAP_SIZE;
    
    arrow_length = BLOCK_SIZE * 3;
    
    arrow.x = player.x + arrow_length * cos(data->player.angle);
    arrow.y = player.y + arrow_length * sin(data->player.angle);
    
	i = 0;
    while (i < arrow_length) {
        t = (double)i / arrow_length;
        new.x = (int)((1 - t) * player.x + t * arrow.x);
        new.y = (int)((1 - t) * player.y + t * arrow.y);
        put_pixel(vector(new.x, new.y), data->mlx.minimap, PURPLE);
		i++;
    }
}
void    put_player(t_data *data)
{
    t_vector    cell;
    t_vector    pixel;

    cell.y = -(PLAYER_SIZE / 2);
	while (cell.y <= PLAYER_SIZE / 2)
	{
		cell.x = -(PLAYER_SIZE / 2);
		while (cell.x <= PLAYER_SIZE / 2)
		{
            pixel.x = (MINIMAP_SIZE) + cell.x;
            pixel.y = (MINIMAP_SIZE) + cell.y;
            put_pixel(pixel, data->mlx.minimap, PLAYER_COLOR);
			cell.x++;
		}
		cell.y++;
	}
}

void	draw_line(t_data *data, int color, t_pos a, t_pos b)
{
	t_pos	tmp;

	if (fabs(b.y - a.y) < fabs(b.x - a.x))
	{
		if (a.x > b.x)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		bresenham_low_slope(data, color, a, b);
	}
	else
	{
		if (a.y > b.y)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		bresenham_high_slope(data, color, a, b);
	}
}
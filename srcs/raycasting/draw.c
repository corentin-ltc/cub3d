#include "cub3d.h"

static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0)
		return ;
	offset = (y * data->mlx_data.img.line_length + x
			* (data->mlx_data.img.bits_per_pixel / 8));
	pixel = data->mlx_data.img.addr + offset;
	*(unsigned int *)pixel = color;
}

void put_block(double pixel_x, double pixel_y, int color, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < BLOCK_SIZE)
	{
		x = 0;
		while (x < BLOCK_SIZE)
		{
			if (!is_too_far(x + pixel_x, y + pixel_y))
				put_pixel(data, x + pixel_x, y + pixel_y, color);
			x++;
		}
		y++;
	}
}

void put_player(int color, t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			j++;
		}
		i++;
	}
}
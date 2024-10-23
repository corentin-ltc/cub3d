#include "cub3d.h"

static void	put_pixel(int x, int y, int color, t_img img)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0)
		return ;
	offset = (y * img.line_length + x * (img.bits_per_pixel / 8));
	pixel = img.addr + offset;
	*(unsigned int *)pixel = color;
}

void put_block(t_pos start, int color, t_img img)
{
	t_pos	pixel;
	int x;
	int y;

	y = -1;
	while (++y < BLOCK_SIZE)
	{
		x = -1;
		while (++x < BLOCK_SIZE)
		{
			pixel.x = start.x + x;
			pixel.y = start.y + y;
			if (get_distance(pixel, img.center) > MINIMAP_SIZE)
				continue;
			if (x == 0 || y == 0)
				put_pixel(pixel.x, pixel.y, WHITE, img);
			else
				put_pixel(pixel.x, pixel.y, color, img);
		}
	}
}

void put_player(int color, t_img img)
{
	int i;
	int j;
	
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			put_pixel(img.center.x + j, img.center.y + i, color, img);
			put_pixel(img.center.x - j, img.center.y + i, color, img);
			put_pixel(img.center.x + j, img.center.y - i, color, img);
			put_pixel(img.center.x - j, img.center.y - i, color, img);
			j++;
		}
		i++;
	}
}

void put_circle(t_pos pos, int radius, int color, t_img img)
{
	const double PI = 3.1415926535;
	double angle;
	t_pos	pixel;

	while (radius >= 0)
	{
		angle = 0;
		while (angle < 360)
		{
			pixel.x = pos.x + (radius * cos(angle * PI / 180));
			pixel.y = pos.y + (radius * sin(angle * PI / 180));
			put_pixel(pixel.x, pixel.y, color, img);
			angle += 1;
		}
		radius--;
	}
}
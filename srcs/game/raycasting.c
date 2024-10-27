#include "cub3d.h"

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

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	t_pos	dir;
	t_pos	end;
	int		distance = VIEW_DIST;

	dir = pos(cos(angle) * distance, sin(angle) * distance);
	end = pos((start.x + dir.x), (start.y + dir.y));
	draw_line(data, color,
		pos(start.x * BLOCK_SIZE, start.y * BLOCK_SIZE),
		pos(end.x * BLOCK_SIZE, end.y * BLOCK_SIZE));
	put_cube(pos(end.x * BLOCK_SIZE, end.y * BLOCK_SIZE), 4, color, data);
}

void	raycasting(t_data *data)
{
	double	angle;
	double	fov;

	angle = data->player.angle;
	fov = data->player.angle - (FOV / 2);
	cast_ray(data, data->player.pos, data->player.angle, PURPLE);
	// cast_ray(data, data->player.pos, data->player.angle - FOV / 2, WHITE);
	// cast_ray(data, data->player.pos, data->player.angle + FOV / 2, WHITE);
}
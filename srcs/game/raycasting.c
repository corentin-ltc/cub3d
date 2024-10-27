#include "cub3d.h"

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	t_ray		ray;
	t_pos	dir;
	int		i;

	ray.start = start;
	ray.angle = angle;
	i = 0;
	while (i < BLOCK_SIZE * VIEW_DIST)
	{
		dir = pos(cos(angle) * i, sin(angle) * i);
		put_minimap_pixel(vector(start.x * BLOCK_SIZE + dir.x, start.y * BLOCK_SIZE + dir.y), color, data);
		i++;
	}
}

void	raycasting(t_data *data)
{
	double	angle;
	double	fov;
	double	step;
	size_t	i;

	fov = (double)FOV * (PI / 180);
	angle = data->player.angle - fov / 2;
	step = fov / WINDOW_WIDTH;
	i = 0;
	while (i <= WINDOW_WIDTH)
	{
		cast_ray(data, data->player.pos, angle, WHITE);
		angle += step;
		i++;
	}
}
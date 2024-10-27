#include "cub3d.h"

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	t_ray	ray;
	t_pos	dir;
	int		i;

	// ray dist
	//horizontal
	if (angle > PI)
		ray.h_dist.y = (int)start.y;
	else
		ray.h_dist.y = start.y + (1 - (start.y - (int)start.y));
	ray.h_dist.x = start.x + (ray.h_dist.y - start.y) / tan(angle);
	put_cube(pos(ray.h_dist.x * BLOCK_SIZE, ray.h_dist.y * BLOCK_SIZE), 1, PURPLE, data);
	//vertical
	if (angle < PI * 0.5 || angle > PI * 1.5)
		ray.v_dist.x = start.x + (1 - (start.x - (int)start.x));
	else
		ray.v_dist.x = (int)start.x;
	ray.v_dist.y = start.y + (ray.v_dist.x - start.x) * tan(angle);
	put_cube(pos(ray.v_dist.x * BLOCK_SIZE, ray.v_dist.y * BLOCK_SIZE), 1, RED, data);
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
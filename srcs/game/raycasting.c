#include "cub3d.h"

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	t_ray		ray;

	ray.start = start;
	ray.angle = angle;
	ray.distance = VIEW_DIST;
	ray.dir = pos(cos(ray.angle) * ray.distance, sin(ray.angle) * ray.distance);
	ray.end = pos((ray.start.x + ray.dir.x), (ray.start.y + ray.dir.y));
	draw_line(data, color,
		pos(ray.start.x * BLOCK_SIZE, ray.start.y * BLOCK_SIZE),
		pos(ray.end.x * BLOCK_SIZE, ray.end.y * BLOCK_SIZE));
	put_cube(pos(ray.end.x * BLOCK_SIZE, ray.end.y * BLOCK_SIZE), 4, color, data);
}

void	raycasting(t_data *data)
{
	double	angle;
	double	fov;

	fov = (double)FOV * (PI / 180);
	cast_ray(data, data->player.pos, data->player.angle, PURPLE);
	cast_ray(data, data->player.pos, data->player.angle - fov / 2, WHITE);
	cast_ray(data, data->player.pos, data->player.angle + fov / 2, WHITE);
	angle = data->player.angle - fov / 2;
	while (angle < data->player.angle + fov / 2)
	{
		cast_ray(data, data->player.pos, angle, WHITE);
		angle += 0.1;
	}
}
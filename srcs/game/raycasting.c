#include "cub3d.h"

static void	get_vertical_intersection(t_ray *ray, t_data *data)
{
	ray->step.x = BLOCK_SIZE / BLOCK_SIZE;
	ray->step.y = BLOCK_SIZE * tan(ray->angle) / BLOCK_SIZE;
	if (ray->angle > PI / 2 && ray->angle < (3 * PI) / 2)
	{
		ray->step.x = -1 * BLOCK_SIZE  / BLOCK_SIZE;
		ray->step.y = -1 * (BLOCK_SIZE * tan(ray->angle))  / BLOCK_SIZE;
		ray->v_inter.x = floor(ray->start.x) - PX;
	}
	else
		ray->v_inter.x = ceil(ray->start.x) + PX;
	ray->v_inter.y = ray->start.y + (ray->v_inter.x - ray->start.x) * tan(ray->angle);
	while (is_wall(data, ray->v_inter.x, ray->v_inter.y) == false)
	{
		ray->v_inter.x += ray->step.x;
		ray->v_inter.y += ray->step.y;
	}
}

static void	get_horizontal_intersection(t_ray *ray, t_data *data)
{
	if (ray->angle < PI && ray->angle > 0)
	{
		ray->step.y = BLOCK_SIZE / BLOCK_SIZE;
		ray->step.x = BLOCK_SIZE / tan(ray->angle)  / BLOCK_SIZE;
		ray->h_inter.y = ceil(ray->start.y) + PX;
	}
	else
	{
		ray->step.y = -1 * BLOCK_SIZE  / BLOCK_SIZE;
		ray->step.x = -1 * (BLOCK_SIZE / tan(ray->angle))  / BLOCK_SIZE;
		ray->h_inter.y = floor(ray->start.y) - PX;
	}
	ray->h_inter.x = ray->start.x + (ray->h_inter.y - ray->start.y) / tan(ray->angle);
	while (is_wall(data, ray->h_inter.x, ray->h_inter.y) == false)
	{
		ray->h_inter.x += ray->step.x;
		ray->h_inter.y += ray->step.y;
	}
}

static t_ray get_ray(t_data *data, t_pos start, double angle)
{
	t_ray	ray;

	ray.start = start;
	ray.angle = angle;
	ray.dir = pos(cos(angle) * 0, sin(angle) * 0);
	get_horizontal_intersection(&ray, data);
	get_vertical_intersection(&ray, data);
	if (get_distance(ray.start, ray.h_inter) > get_distance(ray.start, ray.v_inter))
		ray.end = ray.v_inter;
	else
		ray.end = ray.h_inter;
	ray.distance = get_distance(ray.start, ray.end);
	return (ray);
}

void	raycasting(t_data *data)
{
	double	angle;
	double	step;
	t_ray	ray;
	size_t	i;

	angle = data->player.angle - FOV_RAD / 2;
	step = FOV_RAD / WINDOW_WIDTH;
	i = 0;
	while (i <= WINDOW_WIDTH)
	{
		ray = get_ray(data, data->player.pos, nor_angle(angle));
		if (SHOW_MAP && HIGHLIGHT_WALLS)
			put_cube(pos(ray.end.x * BLOCK_SIZE, ray.end.y * BLOCK_SIZE), 1, CYAN, data);
		if (SHOW_MAP && SHOW_RAYS)
			put_ray(ray, WHITE, data);
		angle += step;
		i++;
	}
}
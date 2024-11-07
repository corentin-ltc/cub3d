#include "cub3d.h"

static void	get_vertical_intersection(t_ray *ray, t_data *data)
{
	double px = PX;

	ray->step.x = 1;
	ray->step.y = MINIMAP_BLOCK_SIZE * tan(ray->angle) / MINIMAP_BLOCK_SIZE;
	if (ray->angle > PI / 2 && ray->angle < (3 * PI) / 2)
	{
		ray->step.x *= -1;
		ray->step.y *= -1;
		px = -PX;
		ray->v_inter.x = floor(ray->start.x);
	}
	else
		ray->v_inter.x = ceil(ray->start.x) + px;
	ray->v_inter.y = ray->start.y + (ray->v_inter.x - ray->start.x) * tan(ray->angle);
	while (is_wall(data, ray->v_inter.x, ray->v_inter.y) == false)
	{
		if (is_wall(data, ray->v_inter.x + px, ray->v_inter.y + PX)
			|| is_wall(data, ray->v_inter.x - px, ray->v_inter.y - PX)
			|| is_wall(data, ray->v_inter.x - px, ray->v_inter.y - PX)
			|| is_wall(data, ray->v_inter.x + px, ray->v_inter.y - PX))
			break ;
		ray->v_inter.x += ray->step.x;
		ray->v_inter.y += ray->step.y;
	}
}

static void	get_horizontal_intersection(t_ray *ray, t_data *data)
{
	double px = PX;

	ray->step.y = 1;
	ray->step.x = MINIMAP_BLOCK_SIZE / tan(ray->angle)  / MINIMAP_BLOCK_SIZE;
	if (ray->angle < PI && ray->angle > 0)
		ray->h_inter.y = ceil(ray->start.y) + px;
	else
	{
		ray->step.y *= -1;
		ray->step.x *= -1;
		px = -PX;
		ray->h_inter.y = floor(ray->start.y);
	}
	ray->h_inter.x = ray->start.x + (ray->h_inter.y - ray->start.y) / tan(ray->angle);
	while (is_wall(data, ray->h_inter.x, ray->h_inter.y) == false)
	{
		if (is_wall(data, ray->h_inter.x - px, ray->h_inter.y - PX)
			|| is_wall(data, ray->h_inter.x + px, ray->h_inter.y + PX)
			|| is_wall(data, ray->h_inter.x + px, ray->h_inter.y - PX)
			|| is_wall(data, ray->h_inter.x + px, ray->h_inter.y + PX))
			break ;
		ray->h_inter.x += ray->step.x;
		ray->h_inter.y += ray->step.y;
	}
}

t_ray cast_ray(t_data *data, t_pos start, double angle)
{
	t_ray	ray;

	ray.start = start;
	ray.angle = angle;
	ray.dir = pos(cos(angle) * 0, sin(angle) * 0);
	get_horizontal_intersection(&ray, data);
	get_vertical_intersection(&ray, data);
	if (get_distance(ray.start, ray.h_inter) > get_distance(ray.start, ray.v_inter))
	{
		ray.end = ray.v_inter;
		if (PI / 2 < ray.angle && ray.angle < (3 * PI) / 2)
			ray.hit = 'W';
		else
			ray.hit = 'E';
	}
	else
	{
		ray.end = ray.h_inter;
		if (PI > ray.angle && ray.angle > 0)
			ray.hit = 'S';
		else
			ray.hit = 'N';
	}
	ray.distance = get_distance(ray.start, ray.end);
	return (ray);
}

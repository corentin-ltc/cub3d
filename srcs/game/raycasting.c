#include "cub3d.h"

static void	get_vertical_intersection(t_ray *ray, t_data *data)
{
	ray->step.x = BLOCK_SIZE / BLOCK_SIZE;
	ray->step.y = BLOCK_SIZE * tan(ray->angle) / BLOCK_SIZE;
	if (ray->angle > PI / 2 && ray->angle < (3 * PI) / 2)
	{
		ray->step.x = -1 * BLOCK_SIZE  / BLOCK_SIZE;
		ray->step.y = -1 * (BLOCK_SIZE * tan(ray->angle))  / BLOCK_SIZE;
		ray->v_dist.x = floor(ray->start.x) - PX;
	}
	else
		ray->v_dist.x = ceil(ray->start.x) + PX;
	ray->v_dist.y = ray->start.y + (ray->v_dist.x - ray->start.x) * tan(ray->angle);
	while (is_wall(data, ray->v_dist.x, ray->v_dist.y) == false)
	{
		// put_cube(pos(ray->v_dist.x * BLOCK_SIZE, ray->v_dist.y * BLOCK_SIZE), 4, YELLOW, data);
		ray->v_dist.x += ray->step.x;
		ray->v_dist.y += ray->step.y;
	}
	// put_cube(pos(ray->v_dist.x * BLOCK_SIZE, ray->v_dist.y * BLOCK_SIZE), 4, RED, data);
}

static void	get_horizontal_intersection(t_ray *ray, t_data *data)
{
	if (ray->angle < PI && ray->angle > 0)
	{
		ray->step.y = BLOCK_SIZE / BLOCK_SIZE;
		ray->step.x = BLOCK_SIZE / tan(ray->angle)  / BLOCK_SIZE;
		ray->h_dist.y = ceil(ray->start.y) + PX;
	}
	else
	{
		ray->step.y = -1 * BLOCK_SIZE  / BLOCK_SIZE;
		ray->step.x = -1 * (BLOCK_SIZE / tan(ray->angle))  / BLOCK_SIZE;
		ray->h_dist.y = floor(ray->start.y) - PX;
	}
	ray->h_dist.x = ray->start.x + (ray->h_dist.y - ray->start.y) / tan(ray->angle);
	while (is_wall(data, ray->h_dist.x, ray->h_dist.y) == false)
	{
		// put_cube(pos(ray->h_dist.x * BLOCK_SIZE, ray->h_dist.y * BLOCK_SIZE), 4, PURPLE, data);
		ray->h_dist.x += ray->step.x;
		ray->h_dist.y += ray->step.y;
	}
	// put_cube(pos(ray->h_dist.x * BLOCK_SIZE, ray->h_dist.y * BLOCK_SIZE), 4, RED, data);
}

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	// printf("---------raycast---------\n");
	t_ray	ray;
	double	i;
	double	distance;

	ray.start = start;
	ray.angle = angle;
	ray.dir = pos(cos(angle) * 0, sin(angle) * 0);
	get_horizontal_intersection(&ray, data);
	get_vertical_intersection(&ray, data);
	if (get_distance(ray.start, ray.h_dist) > get_distance(ray.start, ray.v_dist))
		distance = get_distance(ray.start, ray.v_dist);
	else
		distance = get_distance(ray.start, ray.h_dist);
	i = 0;
	while (i < distance * BLOCK_SIZE && i < MINIMAP_SIZE)
	{
		ray.dir = pos(cos(angle) * i, sin(angle) * i);
		put_minimap_pixel(vector(((start.x * BLOCK_SIZE) + ray.dir.x), ((start.y * BLOCK_SIZE) + ray.dir.y)), color, data);
		i++;
	}
}

void	raycasting(t_data *data)
{
	double	angle;
	double	fov;
	double	step;
	size_t	i;

	// cast_ray(data, data->player.pos, data->player.angle, WHITE);
	// return ;
	fov = (double)FOV * (PI / 180);
	angle = data->player.angle - fov / 2;
	step = fov / WINDOW_WIDTH;
	i = 0;
	while (i <= WINDOW_WIDTH)
	{
		cast_ray(data, data->player.pos, nor_angle(angle), WHITE);
		angle += step;
		i++;
	}
}
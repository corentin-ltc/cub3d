#include "cub3d.h"

static void	get_vertical_intersection(t_ray *ray, t_data *data)
{
	if (ray->angle > PI / 2 && ray->angle < (3 * PI) / 2)
		ray->v_dist.x = floor(ray->start.x) - PX;
	else
		ray->v_dist.x = ceil(ray->start.x) + PX;
	ray->v_dist.y = ray->start.y + (ray->v_dist.x - ray->start.x) * tan(ray->angle);
	if (is_wall(data, ray->v_dist.x, ray->v_dist.y))
		put_cube(pos(ray->v_dist.x * BLOCK_SIZE, ray->v_dist.y * BLOCK_SIZE), 4, RED, data);
	else
		put_cube(pos(ray->v_dist.x * BLOCK_SIZE, ray->v_dist.y * BLOCK_SIZE), 4, YELLOW, data);
	printf("v_dist(%lf,%lf)\n", ray->v_dist.x, ray->v_dist.y);
}

static void	get_horizontal_intersection(t_ray *ray, t_data *data)
{
	if (ray->angle < PI && ray->angle > 0)
		ray->h_dist.y = ceil(ray->start.y) + PX;
	else
		ray->h_dist.y = floor(ray->start.y) - PX;
	ray->h_dist.x = ray->start.x + (ray->h_dist.y - ray->start.y) / tan(ray->angle);
	if (is_wall(data, ray->h_dist.x, ray->h_dist.y))
		put_cube(pos(ray->h_dist.x * BLOCK_SIZE, ray->h_dist.y * BLOCK_SIZE), 4, RED, data);
	else
		put_cube(pos(ray->h_dist.x * BLOCK_SIZE, ray->h_dist.y * BLOCK_SIZE), 4, PURPLE, data);
	printf("h_dist(%lf,%lf)\n", ray->h_dist.x, ray->h_dist.y);
}

void cast_ray(t_data *data, t_pos start, double angle, int color)
{
	printf("---------raycast---------\n");
	t_ray	ray;
	t_pos	dir;
	int		i;

	ray.start = start;
	ray.angle = angle;
	ray.in_wall = false;
	// ray dist
	i = 0;
	while (i < MINIMAP_SIZE && ray.in_wall == false)
	{
		dir = pos(cos(angle) * i, sin(angle) * i);
		put_minimap_pixel(vector(((start.x * BLOCK_SIZE) + dir.x), ((start.y * BLOCK_SIZE) + dir.y)), color, data);
		i++;
	}
	get_horizontal_intersection(&ray, data);
	get_vertical_intersection(&ray, data);
	printf("pos(%lf,%lf)->dir(%lf,%lf)\n", start.x, start.y, cos(angle), sin(angle));
	color++;
}

void	raycasting(t_data *data)
{
	double	angle;
	double	fov;
	double	step;
	size_t	i;

	cast_ray(data, data->player.pos, data->player.angle, WHITE);
	return ;
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
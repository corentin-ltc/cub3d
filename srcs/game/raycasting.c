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
		ray->v_inter.x = floor(ray->start.x) + px;
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
		ray->h_inter.y = floor(ray->start.y) + px;
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

static t_ray get_ray(t_data *data, t_pos start, double angle)
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
		ray.hit = 'v';
	}
	else
	{
		ray.end = ray.h_inter;
		ray.hit = 'h';
	}
	ray.distance = get_distance(ray.start, ray.end);
	ray.distance *= cos(data->player.angle - ray.angle);
	return (ray);
}

void	render_wall(t_data *data, t_ray ray, int i)
{
	double	distance;
	int upper;
	int bottom;
	int color;
	int wall_height;

	if (ray.hit == 'v')
		color = CYAN;
	else
		color = PURPLE;
	upper = WINDOW_HEIGHT / 2;
	bottom = WINDOW_HEIGHT / 2;
	distance = ray.distance * BLOCK_SIZE;
	wall_height = BLOCK_SIZE / distance * PROJECTION_PLANE;
	//printf("distance = %d\n", distance);
	while(wall_height / 2)
	{
		put_pixel(vector(i, upper), data->mlx.game, color);
		put_pixel(vector(i, bottom), data->mlx.game, color);
		upper--;
		bottom++;
		wall_height--;
	}
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
		{
			if (ray.hit == 'v')
				put_cube(pos(ray.end.x * MINIMAP_BLOCK_SIZE, ray.end.y * MINIMAP_BLOCK_SIZE), 1, CYAN, data);
			else if (ray.hit == 'h')
				put_cube(pos(ray.end.x * MINIMAP_BLOCK_SIZE, ray.end.y * MINIMAP_BLOCK_SIZE), 1, PURPLE, data);
		}
		if (SHOW_MAP && SHOW_RAYS)
			put_ray(ray, WHITE, data);
		render_wall(data, ray, i);
		angle += step;
		i++;
	}
}
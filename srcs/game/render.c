#include "cub3d.h"

static int	get_wall_pixel(char direction)
{
	if (direction == 'W')
		return (YELLOW);
	else if (direction == 'E')
		return (DARK_BLUE);
	else if (direction == 'S')
		return (WHITE);
	else if (direction == 'N')
		return (PURPLE);
	return (BLACK);
}

static void	render_wall(t_data *data, t_ray ray, int i)
{
	int wall_height;
	int ceiling_size;
	int y;

	wall_height = 1 / ray.distance * PROJECTION_PLANE;
	ceiling_size = (data->mlx.window_height >> 1) - (wall_height >> 1);
	ceiling_size -= (data->player.z_tilt * 10);
	y = 0;
	while (y <= data->mlx.window_height && y <= ceiling_size)
		put_game_pixel(vector(i, y++), CEILING_COLOR, data);
	while (y <= data->mlx.window_height && y <= ceiling_size + wall_height)
		put_game_pixel(vector(i, y++), get_wall_pixel(ray.hit), data);
	while (y <= data->mlx.window_height)
		put_game_pixel(vector(i, y++), FLOOR_COLOR, data);
}

void	draw_game(t_data *data)
{
	double	angle;
	double	step;
	t_ray	ray;
	int		i;

	angle = data->player.angle - FOV_RAD / 2;
	step = FOV_RAD / data->mlx.window_width;
	i = 0;
	while (i <= data->mlx.window_width)
	{
		ray = cast_ray(data, data->player.pos, nor_angle(angle));
		if (SHOW_MAP && HIGHLIGHT_WALLS)
			put_cube(pos(ray.end.x * MINIMAP_BLOCK_SIZE, ray.end.y * MINIMAP_BLOCK_SIZE), 1, get_direction_color(ray.hit), data);
		if (SHOW_MAP && SHOW_RAYS)
			put_ray(ray, WHITE, data);
		ray.distance *= cos(data->player.angle - ray.angle);
		if (LIGHT)
			render_wall(data, ray, i);
		angle += step;
		i++;
	}
}

#include "cub3d.h"

static void	put_cube(t_pos center, int size, int color, t_data *data)
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

	dir = pos(cos(angle) * (RENDER_DISTANCE / 2), sin(angle) * (RENDER_DISTANCE / 2));
	printf("Angle = %lf, start(%lf,%lf)->dir(%lf,%lf)\n", angle,start.x, start.y, dir.x, dir.y);
	put_cube(pos((start.x + dir.x) * BLOCK_SIZE, (start.y + dir.y) * BLOCK_SIZE), 4, color, data);
}

void	raycasting(t_data *data)
{
	t_pos	player_px;

	player_px = pos(data->player.pos.x * BLOCK_SIZE, data->player.pos.y * BLOCK_SIZE);
	cast_ray(data, data->player.pos, data->player.angle, PURPLE);
	cast_ray(data, data->player.pos, data->player.angle - FOV / 2, WHITE);
	cast_ray(data, data->player.pos, data->player.angle + FOV / 2, WHITE);
}
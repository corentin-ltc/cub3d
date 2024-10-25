#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	if (map[y][x] && map[y][x] == WALL)
		return (true);
	return (false);
}

static void	safe_move(t_data *data, double x_multiplicator, double y_multiplicator)
{
	double	increment;
	t_pos	new_pos;

	increment = SPEED;
	if (data->controls.sprint)
		increment *= 2;
	new_pos.x = data->player.pos.x + (increment * x_multiplicator);
	new_pos.y = data->player.pos.y + (increment * y_multiplicator);
	if (!is_wall(data->map, (int)new_pos.x, (int)new_pos.y))
		data->player.pos = new_pos;
}

void	move_player(t_data *data)
{
	if (data->controls.d)
	{
		safe_move(data, -1 * sin(data->player.angle), 0);
		safe_move(data, 0, +1 * cos(data->player.angle));
	}
	if (data->controls.a)
	{
		safe_move(data, +1 * sin(data->player.angle), 0);
		safe_move(data, 0, -1 * cos(data->player.angle));
	}
	if (data->controls.s)
	{
		safe_move(data, -1 * cos(data->player.angle), 0);
		safe_move(data, 0, -1 * sin(data->player.angle));
	}
	if (data->controls.w)
	{
		safe_move(data, +1 * cos(data->player.angle), 0);
		safe_move(data, 0, +1 * sin(data->player.angle));
	}
}

void	rotate_player(t_data *data)
{
	if (data->controls.left == true)
		data->player.angle -= ROTATION_SPEED;
	if (data->controls.right == true)
		data->player.angle += ROTATION_SPEED;
	if (data->player.angle < 0)
    	data->player.angle += 2 * PI;
	if (data->player.angle >= 2 * PI)
    	data->player.angle -= 2 * PI;
}

void    fill_minimap(t_data *data)
{
    t_vector    cell;

	cell.y = 0;
	if (data->player.pos.y > RENDER_DISTANCE)
		cell.y = (int)data->player.pos.y - RENDER_DISTANCE;
    while (cell.y < data->player.pos.y + RENDER_DISTANCE && data->map[cell.y])
    {
		cell.x = 0;
		if (data->player.pos.x > RENDER_DISTANCE)
			cell.x = (int)data->player.pos.x - RENDER_DISTANCE;
        while (cell.x < data->player.pos.x + RENDER_DISTANCE && data->map[cell.y][cell.x])
        {
            put_block(data, cell);
            cell.x++;
        }
        cell.y++;
    }
    put_player(data);
	put_direction_arrow(data);
}
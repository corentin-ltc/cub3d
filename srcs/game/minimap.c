#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	if (map[y][x] && map[y][x] == WALL)
		return (true);
	return (false);
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
void	move_player(t_data *data)
{
	t_pos	new_pos;
	double	increment;

	new_pos = data->player.pos;
	increment = SPEED;
	if (data->controls.sprint)
		increment *= 2;
	if (data->controls.d)
	{
		new_pos.x -= increment * sin(data->player.angle);
		new_pos.y += increment * cos(data->player.angle);
	}
	if (data->controls.a)
	{
		new_pos.x += increment * sin(data->player.angle);
		new_pos.y -= increment * cos(data->player.angle);
	}
	if (is_wall(data->map, (int)new_pos.x, (int)new_pos.y))
		new_pos = data->player.pos;
	else
		data->player.pos = new_pos;
	if (data->controls.s)
	{
		new_pos.x -= increment * cos(data->player.angle);
		new_pos.y -= increment * sin(data->player.angle);
	}
	if (data->controls.w)
	{
		new_pos.x += increment * cos(data->player.angle);
		new_pos.y += increment * sin(data->player.angle);
	}
	if (!is_wall(data->map, (int)new_pos.x, (int)new_pos.y))
		data->player.pos = new_pos;
}

static void    map_foreach(t_data *data, void (*f)(t_data *, t_vector))
{
    t_vector    cell;

    cell.y = (int)data->player.pos.y - RENDER_DISTANCE;
	if (cell.y < 0)
		cell.y = 0;
    while (cell.y < data->player.pos.y + RENDER_DISTANCE && data->map[cell.y])
    {
        cell.x = (int)data->player.pos.x - RENDER_DISTANCE;
		if (cell.x < 0)
			cell.x = 0;
        while (cell.x < data->player.pos.x + RENDER_DISTANCE && data->map[cell.y][cell.x])
        {
            f(data, cell);
            cell.x++;
        }
        cell.y++;
    }
}

void    fill_minimap(t_data *data)
{
    map_foreach(data, put_block);
    put_player(data);
	put_direction_arrow(data);

}
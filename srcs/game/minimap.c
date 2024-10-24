#include "cub3d.h"

static bool	is_wall(char **map, int x, int y)
{
	if (map[y][x] && map[y][x] == WALL)
		return (true);
	return (false);
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
		new_pos.x += increment;
	if (data->controls.a)
		new_pos.x -= increment;
	if (is_wall(data->map, (int)new_pos.x, (int)new_pos.y))
		new_pos = data->player.pos;
	else
		data->player.pos = new_pos;
	if (data->controls.s)
		new_pos.y += increment;
	if (data->controls.w)
		new_pos.y -= increment;
	if (!is_wall(data->map, (int)new_pos.x, (int)new_pos.y))
		data->player.pos = new_pos;
}

static void    map_foreach(t_data *data, void (*f)(t_data *, t_vector))
{
    t_vector    cell;

    cell.y = 0;
    while (data->map[cell.y])
    {
        cell.x = 0;
        while (data->map[cell.y][cell.x])
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
}
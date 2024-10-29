#include "cub3d.h"

bool	is_wall(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (true);
	if (y >= (int)data->map_height || x >= (int)data->map_width)
		return (true);
	if (data->map[y][x] && data->map[y][x] == WALL)
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
	if (!is_wall(data, (int)new_pos.x, (int)new_pos.y))
		data->player.pos = new_pos;
}

void	move_player(t_data *data)
{
	if (data->controls.l_r)
	{
		safe_move(data, -(data->controls.l_r) * sin(data->player.angle), 0);
		safe_move(data, 0, data->controls.l_r * cos(data->player.angle));
	}
	if (data->controls.u_d)
	{
		safe_move(data, -(data->controls.u_d) * cos(data->player.angle), 0);
		safe_move(data, 0, -(data->controls.u_d) * sin(data->player.angle));
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
	if (data->player.angle > 2 * PI)
    	data->player.angle -= 2 * PI;
}

static void	put_border(t_data *data)
{
	t_pos i;
	double distance;

	i.y = 0;
	while (i.y < (MINIMAP_Y) * 2)
	{
		i.x = 0;
		while (i.x < (MINIMAP_X) * 2)
		{
			distance = get_distance(i, pos(MINIMAP_Y, MINIMAP_Y));
			if (distance > MINIMAP_SIZE && distance < BORDER_WIDTH + MINIMAP_SIZE)
				put_pixel(vector((int) i.x, (int)i.y), data->mlx.minimap, WHITE);
			i.x++;
		}
		i.y++;
	}	
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
	put_border(data);
	put_cube(pos(data->player.pos.x * BLOCK_SIZE, data->player.pos.y * BLOCK_SIZE), PLAYER_SIZE, RED, data);
}
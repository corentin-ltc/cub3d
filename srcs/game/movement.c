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

	increment = data->player.velocity;
	if (data->controls.sprint)
		increment *= 2;
	new_pos.x = data->player.pos.x + (increment * x_multiplicator);
	new_pos.y = data->player.pos.y + (increment * y_multiplicator);
	if (!is_wall(data, (int)new_pos.x, (int)new_pos.y))
		data->player.pos = new_pos;
}

void	move_player(t_data *data)
{
	if (data->controls.l_r == 0 && data->controls.u_d == 0 && data->player.velocity > 0)
		data->player.velocity -= ACCELERATION;
	else if ((data->controls.l_r || data->controls.u_d) && data->player.velocity < MAX_SPEED)
		data->player.velocity += ACCELERATION;
	printf("Player velocity: %lf\n", data->player.velocity);
	if (data->player.velocity <= 0)
	{
		data->player.velocity = 0;
		return ;
	}
	safe_move(data, -(data->controls.l_r) * sin(data->player.angle), 0);
	safe_move(data, 0, data->controls.l_r * cos(data->player.angle));
	safe_move(data, -(data->controls.u_d) * cos(data->player.angle), 0);
	safe_move(data, 0, -(data->controls.u_d) * sin(data->player.angle));
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
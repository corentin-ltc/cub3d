#include "cub3d.h"

static bool	check_collision(double x_increment, double y_increment, t_data *data)
{
	t_pos	new;

	return (false);
	new.x = data->player.pos.x + x_increment;
	new.y = data->player.pos.y + y_increment;
	printf("Checking for collision with : player(%lf,%lf) new(%lf,%lf)\n", data->player.pos.x, data->player.pos.y, new.x, new.y);
	if (data->map[(int)new.y][(int)new.x] == WALL)
		return (true);
	return (false);
}

void	process_input(t_data *data)
{
	if (data->controls.left_pressed == true)
		data->player.angle -= 0.1;
	if (data->controls.right_pressed == true)
		data->player.angle += 0.1;
	if (data->controls.a_pressed == true && !check_collision(-SPEED, 0, data))
		data->player.pos.x -= SPEED;
	if (data->controls.d_pressed == true && !check_collision(+SPEED, 0, data))
		data->player.pos.x += SPEED;
	if (data->controls.w_pressed == true && !check_collision(0, -SPEED, data))
		data->player.pos.y -= SPEED;
	if (data->controls.s_pressed == true && !check_collision(0, +SPEED, data))
		data->player.pos.y += SPEED;
}

void fill_minimap(t_data *data)
{
	t_pos	center;
	t_pos	block;
	int x;
	int y;
	
	y = 0;
	center.y = (BLOCK_SIZE / 2) + MINIMAP_Y;
	center.x = (BLOCK_SIZE / 2) + MINIMAP_X;
	while (data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			process_input(data);
			put_player(RED, data->mlx.minimap);
			// put_circle(center, PLAYER_SIZE, RED, data->mlx.minimap);
			block.x = (x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X;
			block.y = (y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y;
			if (data->map[y][x] == WALL)
				put_block(block, DARK_BLUE, data->mlx.minimap);
			else if (data->map[y][x] == FLOOR)
				put_block(block, BLUE, data->mlx.minimap);
			x++;
		}
		y++;
	}
}

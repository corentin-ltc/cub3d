#include "cub3d.h"

bool	is_collisions(t_data *data, char *movement)
{
	double destination;
	double current;

	current = (data->player.pos.y) / BLOCK_SIZE + data->player.start.y + 0.5;
	if (ft_strcmp(movement, "left") == 0)
		destination = (data->player.pos.x - SPEED) / BLOCK_SIZE + data->player.start.x + 0.5;
	if (ft_strcmp(movement, "right") == 0)
		destination = (data->player.pos.x + SPEED) / BLOCK_SIZE + data->player.start.x + 0.5;
	if ((ft_strcmp(movement, "left") == 0 || ft_strcmp(movement, "right") == 0) && data->map[(int)current][(int)destination] == WALL)
			return (true);
	current = (data->player.pos.x) / BLOCK_SIZE + data->player.start.x + 0.5;
	if (ft_strcmp(movement, "up") == 0)
		destination = (data->player.pos.y - SPEED) / BLOCK_SIZE + data->player.start.y + 0.5;
	if (ft_strcmp(movement, "down") == 0)
		destination = (data->player.pos.y + SPEED) / BLOCK_SIZE + data->player.start.y + 0.5;
	if ((ft_strcmp(movement, "up") == 0 || ft_strcmp(movement, "down") == 0) && data->map[(int)destination][(int)current] == WALL)
			return (true);
	return (false);
}


/* formule pour calculer la distance entre deux points dans le plan cartesien */
bool is_too_far(double pixel_x, double pixel_y)
{
	double player_x;
	double player_y;

	player_x = (BLOCK_SIZE / 2) + MINIMAP_X;
	player_y = (BLOCK_SIZE / 2) + MINIMAP_Y;

	if (sqrt(pow((player_x - pixel_x), 2) + (pow((player_y - pixel_y), 2))) > (double) MINIMAP_SIZE)
		return (true);
	return (false);
}

void	set_new_frame(t_data *data, int x, int y)
{
	if (data->controls.left_pressed == true && !is_collisions(data, "left"))
		data->player.pos.x -= SPEED;
	if (data->controls.right_pressed == true && !is_collisions(data, "right"))
		data->player.pos.x += SPEED;
	if (data->controls.up_pressed == true && !is_collisions(data, "up"))
		data->player.pos.y -= SPEED;
	if (data->controls.down_pressed == true && !is_collisions(data, "down"))
		data->player.pos.y += SPEED;
	// mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->textures->im_player,
	// 						(BLOCK_SIZE / 2) + MINIMAP_X, (BLOCK_SIZE / 2) + MINIMAP_Y);
	put_player(BLUE, data);
	if (data->map[y][x] != WALL && data->map[y][x] != 'W')
	{
		// mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->textures->im_floor,
		// 						(x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
		// 						(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y);
		put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
			(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, RED, data);
	}
	if (data->map[y][x] == WALL)
	{
		/*mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->textures->im_wall,
						(x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X, 
						(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y);*/
		put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
			(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, DARK_BLUE, data);
	}
}

int update(t_data *data)
{
	int x;
	int y;
	long long time;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			set_new_frame(data, x, y);
			x++;
		}
		y++;
	}
	//printf("Coordonness du joueur\ny = %f\tx = %f\n", (data->player.pos.y ) / BLOCK_SIZE + data->player.start.y + 0.5, (data->player.pos.x) / BLOCK_SIZE + data->player.start.x + 0.5);
	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->mlx_data.img.img, 0, 0);
	time = timenow();
	while (timenow() < time + 10)
		usleep(5);
	return (0);
}

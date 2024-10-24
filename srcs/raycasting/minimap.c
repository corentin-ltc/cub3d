#include "cub3d.h"

bool	is_collisions(t_data *data, t_pos new)
{
	t_coord coords;

	coords.x = (new.x) / BLOCK_SIZE + data->player.start.x + 0.5;
	coords.y = (new.y) / BLOCK_SIZE + data->player.start.y + 0.5;
	if (data->map[coords.y][coords.x] == WALL)
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

void	process_input(t_data *data)
{
	t_pos new;

	if (data->controls.left_pressed == true)
		data->player.angle -= 0.0005;
	if (data->controls.right_pressed == true)
		data->player.angle += 0.0005;
	if (data->player.angle < 0)
    	data->player.angle += 2 * M_PI;
	if (data->player.angle >= 2 * M_PI)
    	data->player.angle -= 2 * M_PI;

	if (data->controls.s_pressed == true)
	{
		new.x = data->player.pos.x - SPEED * cos(data->player.angle);
		new.y = data->player.pos.y - SPEED * sin(data->player.angle);
		printf("map[%d][%d]\n", (int)new.y, (int)new.x);
		 if (!is_collisions(data, new))
		{
			data->player.pos.x = new.x;
			data->player.pos.y = new.y;
		}
	}
	if (data->controls.w_pressed == true)
	{
		new.x = data->player.pos.x + SPEED * cos(data->player.angle);
		new.y = data->player.pos.y + SPEED * sin(data->player.angle);
		if (!is_collisions(data, new))
		{
			data->player.pos.x = new.x;
			data->player.pos.y = new.y;
		}
	}
	if (data->controls.a_pressed == true)
	{
    new.x = data->player.pos.x + SPEED * sin(data->player.angle);
    new.y = data->player.pos.y - SPEED * cos(data->player.angle);
    if (!is_collisions(data, new))
    {
        data->player.pos.x = new.x;
        data->player.pos.y = new.y;
    }
	}

	if (data->controls.d_pressed == true)
	{
	    new.x = data->player.pos.x - SPEED * sin(data->player.angle);
	    new.y = data->player.pos.y + SPEED * cos(data->player.angle);
	    if (!is_collisions(data, new))
	    {
	        data->player.pos.x = new.x;
	        data->player.pos.y = new.y;
	    }
	}

}

void set_new_frame(t_data *data, int x, int y)
{
    process_input(data);
    put_player(BLUE, data);
    
    put_direction_arrow(data);

    if (data->map[y][x] != WALL && data->map[y][x] != 'W')
    {
        put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
            (y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, RED, data);
    }
    if (data->map[y][x] == WALL)
    {
        put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
            (y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, DARK_BLUE, data);
    }
}


int update(t_data *data)
{
	int x;
	int y;
	long long time;
	
	new_img(&data->mlx);
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
	printf("Coordonness du joueur\ny = %f\tx = %f\n", (data->player.pos.y ) / BLOCK_SIZE + data->player.start.y + 0.5, (data->player.pos.x) / BLOCK_SIZE + data->player.start.x + 0.5);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img.img, 0, 0);
	mlx_destroy_image(data->mlx.ptr, data->mlx.img.img);
	time = timenow();
	while (timenow() < time + 10)
		usleep(5);
	return (0);
}

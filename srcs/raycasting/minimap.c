#include "cub3d.h"

long long	timenow(void)
{
	struct timeval	tv;
	long long		time_in_ms;	

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}
int	exit_game(t_data *data)
{
	printf("exiting the data\n");
	mlx_destroy_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win);
	mlx_destroy_display(data->mlx_data.mlx_ptr);
	free(data->mlx_data.mlx_ptr);
	exit(1);
	return (0);
}

int handle_input(int keycode, t_data *data)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == XK_Escape)	
		exit_game(data);
	if (keycode == 65363) // droite
		data->controls.right_pressed = true;
	if (keycode == 65361) // gauche
		data->controls.left_pressed = true;
	if (keycode == 65362) // haut
		data->controls.up_pressed = true;
	if (keycode == 65364) // bas
		data->controls.down_pressed = true;
	return (0);
}

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

void	put_pixel(t_mlx_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0)
		return ;
	offset = (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	pixel = data->img.addr + offset;
	*(unsigned int *)pixel = color;
}

void put_block(double pixel_x, double pixel_y, int color, t_mlx_data *mlx_data)
{
	int x;
	int y;

	y = 0;
	while (y < BLOCK_SIZE)
	{
		x = 0;
		while (x < BLOCK_SIZE)
		{
			if (!is_too_far(x + pixel_x, y + pixel_y))
				put_pixel(mlx_data, x + pixel_x, y + pixel_y, color);
			x++;
		}
		y++;
	}
}

void put_player(int color, t_mlx_data *mlx_data)
{
	int i;
	int j;
	
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{	
			put_pixel(mlx_data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(mlx_data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(mlx_data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			put_pixel(mlx_data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			j++;
		}
		i++;
	}
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
	put_player(BLUE, &data->mlx_data);
	if (data->map[y][x] != WALL && data->map[y][x] != 'W')
	{
		// mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->textures->im_floor,
		// 						(x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
		// 						(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y);
		put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
			(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, RED, &data->mlx_data);
	}
	if (data->map[y][x] == WALL)
	{
		/*mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win, data->textures->im_wall,
						(x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X, 
						(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y);*/
		put_block((x - data->player.start.x) * BLOCK_SIZE - (int)data->player.pos.x + MINIMAP_X,
			(y - data->player.start.y) * BLOCK_SIZE - (int)data->player.pos.y + MINIMAP_Y, DARK_BLUE, &data->mlx_data);
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



void	init_textures(t_data *data)
{
	int x;
	int y;

	data->textures.im_wall = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/wall.xpm", &x, &y);
	if (!data->textures.im_wall)
	{
		printf("Failed loading \"wall.xpm\"\n");
		mlx_destroy_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win);
		free_and_exit(data);
	}
	data->textures.im_floor = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/floor.xpm", &x, &y);
	if (!data->textures.im_floor)
	{
		printf("Failed loading \"floor.xpm\"\n");
		mlx_destroy_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win);
		free_and_exit(data);
	}
	data->textures.im_player = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/player.xpm", &x, &y);
	if (!data->textures.im_player)
	{
		printf("Failed loading \"player.xpm\"\n");
		mlx_destroy_window(data->mlx_data.mlx_ptr, data->mlx_data.mlx_win);
		free_and_exit(data);
	}
}

void	free_and_exit(t_data *data)
{
	mlx_destroy_display(data->mlx_data.mlx_ptr);
	free(data->mlx_data.mlx_ptr);
	exit(1);
}

// todo: ameliorer init_textures (index?)
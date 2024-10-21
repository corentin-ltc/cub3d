#include "cub3d.h"

long long	timenow(void)
{
	struct timeval	tv;
	long long		time_in_ms;	

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}
int	exit_game(t_game *game)
{
	printf("exiting the game\n");
	mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win);
	mlx_destroy_display(game->mlx_data->mlx_ptr);
	free(game->mlx_data->mlx_ptr);
	exit(1);
	return (0);
}

int handle_input(int keycode, t_game *game)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == XK_Escape)	
		exit_game(game);
	if (keycode == 65363) // droite
		game->controls->right_pressed = true;
	if (keycode == 65361) // gauche
		game->controls->left_pressed = true;
	if (keycode == 65362) // haut
		game->controls->up_pressed = true;
	if (keycode == 65364) // bas
		game->controls->down_pressed = true;
	return (0);
}

bool	is_collisions(t_game *game, char *movement)
{
	double destination;
	double current;

	current = (game->player->d_pos_y) / BLOCK_SIZE + game->player->start_y + 0.5;
	if (ft_strcmp(movement, "left") == 0)
		destination = (game->player->d_pos_x - SPEED) / BLOCK_SIZE + game->player->start_x + 0.5;
	if (ft_strcmp(movement, "right") == 0)
		destination = (game->player->d_pos_x + SPEED) / BLOCK_SIZE + game->player->start_x + 0.5;
	if ((ft_strcmp(movement, "left") == 0 || ft_strcmp(movement, "right") == 0) && game->map[(int)current][(int)destination] == WALL)
			return (true);
	current = (game->player->d_pos_x) / BLOCK_SIZE + game->player->start_x + 0.5;
	if (ft_strcmp(movement, "up") == 0)
		destination = (game->player->d_pos_y - SPEED) / BLOCK_SIZE + game->player->start_y + 0.5;
	if (ft_strcmp(movement, "down") == 0)
		destination = (game->player->d_pos_y + SPEED) / BLOCK_SIZE + game->player->start_y + 0.5;
	if ((ft_strcmp(movement, "up") == 0 || ft_strcmp(movement, "down") == 0) && game->map[(int)destination][(int)current] == WALL)
			return (true);
	return (false);
}

void	put_pixel(t_mlx_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0)
		return ;
	offset = (y * data->img->line_length + x
			* (data->img->bits_per_pixel / 8));
	pixel = data->img->addr + offset;
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

void	set_new_frame(t_game *game, int x, int y)
{
	if (game->controls->left_pressed == true && !is_collisions(game, "left"))
		game->player->d_pos_x -= SPEED;
	if (game->controls->right_pressed == true && !is_collisions(game, "right"))
		game->player->d_pos_x += SPEED;
	if (game->controls->up_pressed == true && !is_collisions(game, "up"))
		game->player->d_pos_y -= SPEED;
	if (game->controls->down_pressed == true && !is_collisions(game, "down"))
		game->player->d_pos_y += SPEED;
	// mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->textures->im_player,
	// 						(BLOCK_SIZE / 2) + MINIMAP_X, (BLOCK_SIZE / 2) + MINIMAP_Y);
	if (game->map[y][x] != WALL && game->map[y][x] != 'W')
	{
		// mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->textures->im_floor,
		// 						(x - game->player->start_x) * BLOCK_SIZE - (int)game->player->d_pos_x + MINIMAP_X,
		// 						(y - game->player->start_y) * BLOCK_SIZE - (int)game->player->d_pos_y + MINIMAP_Y);
		put_block((x - game->player->start_x) * BLOCK_SIZE - (int)game->player->d_pos_x + MINIMAP_X,
			(y - game->player->start_y) * BLOCK_SIZE - (int)game->player->d_pos_y + MINIMAP_Y, BLUE, game->mlx_data);
	}
	if (game->map[y][x] == WALL)
	{
		/*mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->textures->im_wall,
						(x - game->player->start_x) * BLOCK_SIZE - (int)game->player->d_pos_x + MINIMAP_X, 
						(y - game->player->start_y) * BLOCK_SIZE - (int)game->player->d_pos_y + MINIMAP_Y);*/
		put_block((x - game->player->start_x) * BLOCK_SIZE - (int)game->player->d_pos_x + MINIMAP_X,
			(y - game->player->start_y) * BLOCK_SIZE - (int)game->player->d_pos_y + MINIMAP_Y, RED, game->mlx_data);
	}
}

int update(t_game *game)
{
	int x;
	int y;
	long long time;

	y = 0;
	while (game->map[y] && y < 5)
	{
		x = 0;
		while(game->map[y][x])
		{
			set_new_frame(game, x, y);
			x++;
		}
		y++;
	}
	//printf("Coordonness du joueur\ny = %f\tx = %f\n", (game->player->d_pos_y ) / BLOCK_SIZE + game->player->start_y + 0.5, (game->player->d_pos_x) / BLOCK_SIZE + game->player->start_x + 0.5);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->mlx_data->img->img, 0, 0);
	time = timenow();
	while (timenow() < time + 10)
		usleep(5);
	return (0);
}



void	init_textures(t_mlx_data *mlx_data, t_textures *textures, t_game *game)
{
	int x;
	int y;

	game->textures = textures;
	game->mlx_data = mlx_data;
	textures->im_wall = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
			"assets/textures/wall.xpm", &x, &y);
	if (!textures->im_wall)
	{
		printf("Failed loading \"wall.xpm\"\n");
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_win);
		free_and_exit(mlx_data, game);
	}
	textures->im_floor = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
			"assets/textures/floor.xpm", &x, &y);
	if (!textures->im_floor)
	{
		printf("Failed loading \"floor.xpm\"\n");
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_win);
		free_and_exit(mlx_data, game);
	}
	textures->im_player = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
			"assets/textures/player.xpm", &x, &y);
	if (!textures->im_player)
	{
		printf("Failed loading \"player.xpm\"\n");
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_win);
		free_and_exit(mlx_data, game);
	}
}

void	free_and_exit(t_mlx_data *data, t_game *game)
{
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(1);
	game++;
	//freemap(game->map, 0, 1);
}

// todo: ameliorer init_textures (index?)
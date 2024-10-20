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
		game->player->right_pressed = true;
	if (keycode == 65361) // gauche
		game->player->left_pressed = true;
	if (keycode == 65362) // haut
		game->player->up_pressed = true;
	if (keycode == 65364) // bas
		game->player->down_pressed = true;
	return (0);
}

int update(t_game *game)
{
	int x;
	int y;
	long long time;

	x = 0;
	time = timenow();
	//printf("game->player->position_y = %d\n", game->player->position_y);
	// printf("game->player->left_pressed = %d\n", game->player->left_pressed);
	// printf("game->player->right_pressed = %d\n", game->player->right_pressed);
	// printf("game->player->up_pressed = %d\n", game->player->up_pressed);
	// printf("game->player->down_pressed = %d\n", game->player->down_pressed);
	while (game->map[x] && x < 5)
	{
		y = 0;
		while(game->map[x][y])
		{
			if (game->player->left_pressed == 1)
				game->player->posy += SPEED;
			if (game->player->right_pressed == 1)
				game->player->posy -= SPEED;
			if (game->player->up_pressed == 1)
				game->player->posx += SPEED;
			if (game->player->down_pressed == 1)
				game->player->posx -= SPEED;
			if (game->player->posx > game->player->position_x + 1)
				game->player->position_x += 1;
			if (game->player->posx < game->player->position_x - 1)
				game->player->position_x -= 1;
			if (game->player->posy > game->player->position_y + 1)
				game->player->position_y += 1;
			if (game->player->posy < game->player->position_y - 1)
				game->player->position_y -= 1;
			if (game->map[x][y] == '1')
			{
				mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
								game->textures->im_wall, y * 64 + game->player->position_y , x * 64 + game->player->position_x );
			}
			if (game->map[x][y] == '0' || game->map[x][y] == ' ')
			{
				mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
								game->textures->im_floor, y * 64 + game->player->position_y , x * 64 + game->player->position_x );
			}
			if (game->map[x][y] == 'W')
			{
				mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
								game->textures->im_player, y * 64, x * 64);
			}
			y++;
		}
		x++;
	}
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

// todo: gerer mouvement diagonale
// enlever trainees des murs
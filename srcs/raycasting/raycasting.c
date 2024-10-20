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

int update(t_game *game)
{
	int x;
	int y;
	long long time;

	y = 0;
	time = timenow();
	//printf("game->player->pos_x = %d\n", game->player->pos_x);
	// printf("game->player->left_pressed = %d\n", game->player->left_pressed);
	// printf("game->player->right_pressed = %d\n", game->player->right_pressed);
	// printf("game->player->up_pressed = %d\n", game->player->up_pressed);
	// printf("game->player->down_pressed = %d\n", game->player->down_pressed);
	while (game->map[y] && y < 5)
	{
		x = 0;
		while(game->map[y][x])
		{
			if (game->controls->left_pressed == true)
				game->player->d_pos_x -= SPEED;
			if (game->controls->right_pressed == true)
				game->player->d_pos_x += SPEED;
			if (game->controls->up_pressed == true)
				game->player->d_pos_y += SPEED;
			if (game->controls->down_pressed == true)
				game->player->d_pos_y -= SPEED;
			mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
								game->textures->im_player, 30, 30);
			if (game->map[y][x] == '1')
			{
				mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->textures->im_wall,
								(x - game->player->start_x) * IMAGE_SIZE - (int)game->player->d_pos_x, 
								(y - game->player->start_y) * IMAGE_SIZE + (int)game->player->d_pos_y);
			}
			if (game->map[y][x] == '0' || game->map[y][x] == ' ')
			{
				mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->textures->im_floor,
										(x - game->player->start_x) * IMAGE_SIZE - (int)game->player->d_pos_x ,
										(y - game->player->start_y) * IMAGE_SIZE + (int)game->player->d_pos_y );
			}
			x++;
		}
		y++;
	}
	printf("Coordonness du joueur\ny = %d\tx = %d\n", (int)game->player->d_pos_y / 64 + game->player->start_y, (int)game->player->d_pos_x / 64 + game->player->start_x);
	printf("Coordonness du joueur\ny = %f\tx = %f\n", game->player->d_pos_y / 64, game->player->d_pos_x / 64);
	
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
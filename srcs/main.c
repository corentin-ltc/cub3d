#include "cub3d.h"

int	release_input(int keycode, t_game *game)
{
	if (keycode == 65363) // droite
		game->controls->right_pressed = false;
	if (keycode == 65361) // gauche
		game->controls->left_pressed = false;
	if (keycode == 65362) // haut
		game->controls->up_pressed = false;
	if (keycode == 65364) // bas
		game->controls->down_pressed = false;

	return (0);
}

void game_loop(t_data *data)
{
	t_mlx_data		mlx_data;
	t_textures		textures;
	t_game			game;
	t_controls		controls;
	t_img			img;

	game.map = data->map;
	game.controls = &controls;
	game.player = &data->player;
	controls.down_pressed = false;
	controls.up_pressed = false;
	controls.left_pressed = false;
	controls.right_pressed = false;
	mlx_data.img = &img;
	init_mlx(&mlx_data);
	init_textures(&mlx_data, &textures, &game);
	mlx_hook(mlx_data.mlx_win, DestroyNotify, 0, exit_game, &game);
	mlx_hook(mlx_data.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(mlx_data.mlx_win, 3, 1L << 1, release_input, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, update, &game);
	mlx_loop(mlx_data.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data);
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
		exit_error(ERR_FILE_OPEN);
	get_elements(&data);
	get_map(&data);
	check_map(&data);
	show_data(data);
	game_loop(&data);
	free_data(&data);
	return (0);
}
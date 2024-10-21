#include "cub3d.h"

int	release_input(int keycode, t_data *data)
{
	if (keycode == 65363) // droite
		data->controls.right_pressed = false;
	if (keycode == 65361) // gauche
		data->controls.left_pressed = false;
	if (keycode == 65362) // haut
		data->controls.up_pressed = false;
	if (keycode == 65364) // bas
		data->controls.down_pressed = false;

	return (0);
}

void game_loop(t_data *data)
{
	data->controls.down_pressed = false;
	data->controls.up_pressed = false;
	data->controls.left_pressed = false;
	data->controls.right_pressed = false;
	init_mlx(&data->mlx_data);
	init_textures(data);
	mlx_hook(data->mlx_data.mlx_win, DestroyNotify, 0, exit_game, data);
	mlx_hook(data->mlx_data.mlx_win, 2, 1L << 0, handle_input, data);
	mlx_hook(data->mlx_data.mlx_win, 3, 1L << 1, release_input, data);
	mlx_loop_hook(data->mlx_data.mlx_ptr, update, data);
	mlx_loop(data->mlx_data.mlx_ptr);
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
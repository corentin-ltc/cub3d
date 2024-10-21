#include "cub3d.h"

static int handle_input(int keycode, t_data *data)
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

static int	release_input(int keycode, t_data *data)
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

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_data.mlx_win, DestroyNotify, 0, exit_game, data);
	mlx_hook(data->mlx_data.mlx_win, 2, 1L << 0, handle_input, data);
	mlx_hook(data->mlx_data.mlx_win, 3, 1L << 1, release_input, data);
	mlx_loop_hook(data->mlx_data.mlx_ptr, update, data);
}
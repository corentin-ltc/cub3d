#include "cub3d.h"

static int handle_input(int keycode, t_data *data)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == XK_Escape)	
		exit_game(data);
	if (keycode == XK_Right) // droite
		data->controls.right_pressed = true;
	if (keycode == XK_Left) // gauche
		data->controls.left_pressed = true;
	if (keycode == XK_Up) // haut
		data->controls.up_pressed = true;
	if (keycode == XK_Down) // bas
		data->controls.down_pressed = true;
	return (0);
}

static int	release_input(int keycode, t_data *data)
{
	if (keycode == XK_Right) // droite
		data->controls.right_pressed = false;
	if (keycode == XK_Left) // gauche
		data->controls.left_pressed = false;
	if (keycode == XK_Up) // haut
		data->controls.up_pressed = false;
	if (keycode == XK_Down) // bas
		data->controls.down_pressed = false;
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, DestroyNotify, 0, exit_game, data);
	mlx_hook(data->mlx.win, 2, 1L << 0, handle_input, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, release_input, data);
	mlx_loop_hook(data->mlx.ptr, update, data);
}
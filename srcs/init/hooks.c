#include "cub3d.h"

/**
* @date 21/10/2024
* @file hooks.c
* @brief Updates movement booleans
**/
static int	handle_input(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		exit_game(data);
	if (keycode == XK_Right)
		data->controls.right_pressed = true;
	if (keycode == XK_Left)
		data->controls.left_pressed = true;
	if (keycode == XK_Up)
		data->controls.up_pressed = true;
	if (keycode == XK_Down)
		data->controls.down_pressed = true;
	if (keycode == XK_w) 
		data->controls.w_pressed = true;
	if (keycode == XK_s) 
		data->controls.s_pressed = true;
	if (keycode == XK_a) 
		data->controls.a_pressed = true;
	if (keycode == XK_d) 
		data->controls.d_pressed = true;
	return (0);
}

/**
* @date 21/10/2024
* @file hooks.c
* @brief Updates movement booleans
**/
static int	release_input(int keycode, t_data *data)
{
	if (keycode == XK_Right)
		data->controls.right_pressed = false;
	if (keycode == XK_Left)
		data->controls.left_pressed = false;
	if (keycode == XK_Up)
		data->controls.up_pressed = false;
	if (keycode == XK_Down)
		data->controls.down_pressed = false;
	if (keycode == XK_w) 
		data->controls.w_pressed = false;
	if (keycode == XK_s) 
		data->controls.s_pressed = false;
	if (keycode == XK_a) 
		data->controls.a_pressed = false;
	if (keycode == XK_d)
		data->controls.d_pressed = false;
	return (0);
}

/**
* @date 21/10/2024
* @file hooks.c
* @brief Sets mlx_hook for key_press, key_release, mlx_loop and DestroyNotify
**/
void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, DestroyNotify, 0, exit_game, data);
	mlx_hook(data->mlx.win, 2, 1L << 0, handle_input, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, release_input, data);
	mlx_loop_hook(data->mlx.ptr, game_loop, data);
}

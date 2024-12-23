#include "cub3d.h"

void	process_input(t_data *data)
{
	data->controls.l_r = 0;
	if (data->controls.a && !data->controls.d)
		data->controls.l_r = -1;
	else if (data->controls.d && !data->controls.a)
		data->controls.l_r = 1;
	data->controls.u_d = 0;
	if (data->controls.w && !data->controls.s)
		data->controls.u_d = -1;
	else if (data->controls.s && !data->controls.w)
		data->controls.u_d = 1;
}

/**
* @date 21/10/2024
* @file hooks.c
* @brief Updates movement booleans
**/
static int	press_input(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		exit_game(data);
	if (keycode == XK_Tab)
		data->controls.settings = !data->controls.settings;
	if (keycode == XK_Right)
		data->controls.right = true;
	if (keycode == XK_Left)
		data->controls.left = true;
	if (keycode == XK_Up)
		data->controls.up = true;
	if (keycode == XK_Down)
		data->controls.down = true;
	if (keycode == XK_w) 
		data->controls.w = true;
	if (keycode == XK_s) 
		data->controls.s = true;
	if (keycode == XK_a) 
		data->controls.a = true;
	if (keycode == XK_d) 
		data->controls.d = true;
	if (keycode == XK_Shift_L)
		data->controls.sprint = true;
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
		data->controls.right = false;
	if (keycode == XK_Left)
		data->controls.left = false;
	if (keycode == XK_Up)
		data->controls.up = false;
	if (keycode == XK_Down)
		data->controls.down = false;
	if (keycode == XK_w) 
		data->controls.w = false;
	if (keycode == XK_s) 
		data->controls.s = false;
	if (keycode == XK_a) 
		data->controls.a = false;
	if (keycode == XK_d)
		data->controls.d = false;
	if (keycode == XK_Shift_L)
		data->controls.sprint = false;
	return (0);
}

static int	mouse_movements(int x,int y, t_data *data)
{
	data->player.angle += (x - (data->mlx.window_width >> 1)) * MOUSE_X_SPEED;
	data->player.z_tilt +=  (y  - (data->mlx.window_height >> 1)) * MOUSE_Y_SPEED;
	mlx_mouse_move(data->mlx.ptr, data->mlx.win, data->mlx.window_width >> 1, data->mlx.window_height >> 1);
	return (0);
}
static int	mouse_buttons(int button,int x,int y, t_data *data)
{
	if (button == 3)
		mlx_mouse_show(data->mlx.ptr, data->mlx.win);
	return (0);
	printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
}
/**
* @date 21/10/2024
* @file hooks.c
* @brief Sets mlx_hook for key_press, key_release, mlx_loop and DestroyNotify
**/
void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, DestroyNotify, 0, exit_game, data);
	mlx_hook(data->mlx.win, KeyPress , KeyPressMask, press_input, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, release_input, data);
	mlx_mouse_hook(data->mlx.win, mouse_buttons, data);
	mlx_mouse_hide(data->mlx.ptr, data->mlx.win);
	mlx_mouse_move(data->mlx.ptr, data->mlx.win, data->mlx.window_width >> 1, data->mlx.window_height >> 1);
	mlx_hook(data->mlx.win, MotionNotify, PointerMotionMask, mouse_movements, data);
	mlx_loop_hook(data->mlx.ptr, game_loop, data);
}

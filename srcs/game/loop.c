#include "cub3d.h"

/*
seconds for a frame = one second / frames per second
we wait for the remaining time to reach the desired fps
sleep if the framerate would be higher than the max_fps
*/
static void	sleep_based_on_max_fps(t_data *data, int max_fps)
{
	time_t		time_since_last_frame;

	time_since_last_frame = timenow() - data->mlx.last_frame;
	while (time_since_last_frame < 1000 / max_fps)
		time_since_last_frame = timenow() - data->mlx.last_frame;
}

/*
frames per second = one second / seconds since last frame
*/
static void	show_fps(t_data *data)
{
	static long long	last_print = 0;
	static int			fps = 0;

	// printf("Now: %lld, Last time: %lld, Diff: %lld\n", timenow(), data->mlx.last_frame, timenow() - data->mlx.last_frame);
	if (timenow() - last_print >= FPS_INTERVAL)
	{
		last_print = timenow();
		fps = 1000 / (timenow() - data->mlx.last_frame);
	}
	mlx_string_put(data->mlx.ptr, data->mlx.win, 20, 20, RED, ft_itoa(fps));
}

static void	new_img(t_mlx_data mlx, t_img *img)
{
	img->img = mlx_new_image(mlx.ptr, img->width, img->height);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (!img->addr)
		return ;
}

static void	put_img(t_mlx_data mlx, t_img *img, int x, int y)
{
    mlx_put_image_to_window(mlx.ptr, mlx.win, img->img, x, y);
    mlx_destroy_image(mlx.ptr, img->img);
	img->img = NULL;
}

static void show_cursor(t_data *data, int color)
{
	t_pos	win_center;
	t_ray	line;

	win_center = pos(data->mlx.window_width / 2, data->mlx.window_height / 2);
	line.distance = CURSOR_LENGTH;
	put_pixel(vector(win_center.x, win_center.y), data->mlx.game, RED);
	line.angle = 0;
	line.start = pos(win_center.x + CURSOR_SPACE, win_center.y);
	put_ray(line, color, data, false);
	line.angle = PI * 0.5;
	line.start = pos(win_center.x, win_center.y + CURSOR_SPACE);
	put_ray(line, color, data, false);
	line.angle = PI;
	line.start = pos(win_center.x - CURSOR_SPACE, win_center.y);
	put_ray(line, color, data, false);
	line.angle = PI * 1.5;
	line.start = pos(win_center.x, win_center.y - CURSOR_SPACE);
	put_ray(line, color, data, false);
}

int game_loop(t_data *data)
{
	data->mlx.delta_time = timenow() - data->mlx.last_frame;
	data->mlx.last_frame = timenow();
	new_img(data->mlx, &data->mlx.settings);
	fill_settings(data);
	//put_img(data->mlx, &data->mlx.settings, SETTINGS_X, SETTINGS_Y);
	if (data->controls.settings)
		show_settings(data);
	else
	{
		new_img(data->mlx, &data->mlx.game);
		process_input(data);
		rotate_player(data);
		move_player(data);
		raycasting(data);
		if (SHOW_MAP)
			fill_minimap(data);
		show_cursor(data, CURSOR_COLOR);
		put_img(data->mlx, &data->mlx.game, 0, 0);
		sleep_based_on_max_fps(data, MAX_FPS);
		show_fps(data);
	}
	return (0);
}
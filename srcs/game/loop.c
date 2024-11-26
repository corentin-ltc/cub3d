/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbellila <nbellila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:47:14 by nbellila          #+#    #+#             */
/*   Updated: 2024/11/26 18:47:14 by nbellila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	game_loop(t_data *data)
{
	data->mlx.delta_time = timenow() - data->mlx.last_frame;
	data->mlx.last_frame = timenow();
	{
		new_img(data->mlx, &data->mlx.game);
		process_input(data);
		rotate_player(data);
		move_player(data);
		if (SHOW_MAP)
			draw_minimap(data);
		draw_game(data);
		put_img(data->mlx, &data->mlx.game, 0, 0);
	}
	sleep_based_on_max_fps(data, MAX_FPS);
	show_fps(data);
	return (0);
}

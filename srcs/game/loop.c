#include "cub3d.h"

static void	sleep_based_on_fps(int fps)
{
	long long	start;

	start = timenow();
	while (timenow() < start + 1000 / fps)
		usleep(1);
}

static void	new_img(const t_data *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (!img->addr)
		return ;
}

static void	replace_img(const t_data *data, t_img previous, t_img new)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, new.img, 0, 0);
	if (previous.img)
		mlx_destroy_image(data->mlx.ptr, previous.img);
}

int game_loop(t_data *data)
{
	t_img prev_minimap;
	
	printf("player(%lf,%lf)\n", data->player.pos.x, data->player.pos.y);
	prev_minimap = data->mlx.minimap;
	new_img(data, &data->mlx.minimap);
	fill_minimap(data);
	replace_img(data, prev_minimap, data->mlx.minimap);
	sleep_based_on_fps(30);
	return (0);
}
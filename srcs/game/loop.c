#include "cub3d.h"

static void	sleep_based_on_fps(int fps)
{
	long long	start;

	start = timenow();
	while (timenow() < start + 1000 / fps)
		usleep(1);
}

static void	new_img(void *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (!img->addr)
		return ;
}

static void show_game_info(t_data *data)
{
    printf("Player(x:%lf,y:%lf,angle:%lf)\n", data->player.pos.x, data->player.pos.y, data->player.angle);
}

int game_loop(t_data *data)
{
    show_game_info(data);
    new_img(data->mlx.ptr, &data->mlx.minimap);
    fill_minimap(data);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.minimap.img, 0, 0);
    mlx_destroy_image(data->mlx.ptr, data->mlx.minimap.img);
    sleep_based_on_fps(30);
    return (0);
}
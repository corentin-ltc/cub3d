#include "cub3d.h"

static void	sleep_based_on_fps(int fps)
{
	long long	start;

	start = timenow();
	while (timenow() < start + 1000 / fps)
		usleep(1);
}

static void	new_img(t_mlx_data mlx, t_img *img)
{
	img->img = mlx_new_image(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
	if (!img->addr)
		return ;
}

static void	put_img(t_mlx_data mlx, t_img *img)
{
    mlx_put_image_to_window(mlx.ptr, mlx.win, img->img, 0, 0);
    mlx_destroy_image(mlx.ptr, img->img);
	img->img = NULL;
}

int game_loop(t_data *data)
{
    printf("Player(x:%lf,y:%lf,angle:%lf,l_r:%d,u_d:%d)\n", data->player.pos.x, data->player.pos.y, data->player.angle, data->controls.l_r, data->controls.u_d);
    new_img(data->mlx, &data->mlx.minimap);
	process_input(data);
	move_player(data);
	rotate_player(data);
    fill_minimap(data);
	put_img(data->mlx, &data->mlx.minimap);
    sleep_based_on_fps(30);
    return (0);
}
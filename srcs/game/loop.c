#include "cub3d.h"

static void	sleep_based_on_fps(int fps)
{
	long long	start;

	start = timenow();
	while (timenow() < start + 1000 / fps)
		usleep(1);
}

static void	new_img(t_mlx_data mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx.ptr, width, height);
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

int game_loop(t_data *data)
{
	new_img(data->mlx, &data->mlx.minimap, MINIMAP_FULL_SIZE, MINIMAP_FULL_SIZE);
	process_input(data);
	rotate_player(data);
	move_player(data);
	raycasting(data);
	if (SHOW_MAP && LIGHT)
		fill_minimap(data);
	put_img(data->mlx, &data->mlx.minimap, BORDER_WIDTH, BORDER_WIDTH);
    sleep_based_on_fps(FPS);
    return (0);
}
#include "cub3d.h"

void	*init_mlx(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (NULL);
	data->img.img = mlx_new_image(data->mlx_ptr, 1000, 1010);
	if (!data->img.img)
		return (NULL);
	data->mlx_win = mlx_new_window(data->mlx_ptr, 1000, 1010, TITLE);
	if (!data->mlx_win)
		return (NULL);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	if (!data->img.addr)
		return (NULL);
	return (data);
}
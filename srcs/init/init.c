#include "cub3d.h"

/*Sets default value to prevent invalid free/read*/
/*Does not allocated anything*/
static void	set_default_values(t_data *data)
{
	data->controls.down_pressed = false;
	data->controls.up_pressed = false;
	data->controls.left_pressed = false;
	data->controls.right_pressed = false;
	data->player.angle = -42;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->tmp = NULL;
	data->mlx_data.img.img = NULL;
	data->mlx_data.mlx_ptr = NULL;
	data->mlx_data.mlx_win = NULL;
}

/*Initializes mlx, mlx images and mlx windows*/
/*Exits on allocation error*/
static void	init_mlx(t_data *data)
{
	data->mlx_data.mlx_ptr = mlx_init();
	if (!data->mlx_data.mlx_ptr)
		exit_free(ERR_MALLOC, data);
	data->mlx_data.img.img = mlx_new_image(data->mlx_data.mlx_ptr, 1000, 1010);
	if (!data->mlx_data.img.img)
		exit_free(ERR_MALLOC, data);
	data->mlx_data.mlx_win = mlx_new_window(data->mlx_data.mlx_ptr, 1000, 1010, TITLE);
	if (!data->mlx_data.mlx_win)
		exit_free(ERR_MALLOC, data);
	data->mlx_data.img.addr = mlx_get_data_addr(data->mlx_data.img.img,
			&data->mlx_data.img.bits_per_pixel,
			&data->mlx_data.img.line_length,
			&data->mlx_data.img.endian);
	if (!data->mlx_data.img.addr)
		exit_free(ERR_MALLOC, data);
}

/*Opens and initializes the textures given by the user*/
/*Exits on error*/
static void	init_textures(t_data *data)
{
	int x;
	int y;

	data->textures.im_wall = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/wall.xpm", &x, &y);
	if (!data->textures.im_wall)
		exit_free(ERR_UNDEFINED, data);
	data->textures.im_floor = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/floor.xpm", &x, &y);
	if (!data->textures.im_floor)
		exit_free(ERR_UNDEFINED, data);
	data->textures.im_player = mlx_xpm_file_to_image(data->mlx_data.mlx_ptr,
			"assets/textures/player.xpm", &x, &y);
	if (!data->textures.im_player)
		exit_free(ERR_UNDEFINED, data);
}
void	init_data(t_data *data, char *filename)
{
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		exit_error(ERR_FILE_OPEN);
	set_default_values(data);
	get_elements(data);
	get_map(data);
	check_map(data);
	init_mlx(data);
	init_textures(data);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_data.mlx_win, DestroyNotify, 0, exit_game, &data);
	mlx_hook(data->mlx_data.mlx_win, 2, 1L << 0, handle_input, &data);
	mlx_hook(data->mlx_data.mlx_win, 3, 1L << 1, release_input, &data);
	mlx_loop_hook(data->mlx_data.mlx_ptr, update, &data);
}
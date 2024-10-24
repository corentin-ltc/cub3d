#include "cub3d.h"

/**
* @date 21/10/2024
* @file init.c
* @brief Set values to NULL to prevent invalid read/free
**/
static void	set_default_values(t_data *data)
{
	data->controls.down = false;
	data->controls.up = false;
	data->controls.left = false;
	data->controls.right = false;
	data->controls.sprint = false;
	data->controls.w = false;
	data->controls.s = false;
	data->controls.a = false;
	data->controls.d = false;
	data->player.angle = 0;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->tmp = NULL;
	data->mlx.ptr = NULL;
	data->mlx.win = NULL;
	data->mlx.minimap.img = NULL;
	data->mlx.minimap.center.x = (BLOCK_SIZE / 2) + MINIMAP_X;
	data->mlx.minimap.center.y = (BLOCK_SIZE / 2) + MINIMAP_Y;
}

/**
* @date 21/10/2024
* @file init.c
* @brief Initializes an mlx pointer, image and window
* @exception Exits the program on allocation error
**/
static void	init_mlx(t_data *data)
{
	data->mlx.ptr = mlx_init();
	if (!data->mlx.ptr)
		exit_free(ERR_MALLOC, data);
	data->mlx.minimap.img = mlx_new_image(data->mlx.ptr, 1000, 1010);
	if (!data->mlx.minimap.img)
		exit_free(ERR_MALLOC, data);
	data->mlx.win = mlx_new_window(data->mlx.ptr, 1000, 1010, TITLE);
	if (!data->mlx.win)
		exit_free(ERR_MALLOC, data);
	data->mlx.minimap.addr = mlx_get_data_addr(data->mlx.minimap.img,
			&data->mlx.minimap.bits_per_pixel,
			&data->mlx.minimap.line_length,
			&data->mlx.minimap.endian);
	if (!data->mlx.minimap.addr)
		exit_free(ERR_MALLOC, data);
}

/**/
/*Exits on error*/
/**
* @date 21/10/2024
* @file init.c
* @brief loads the textures given by the user
* @exception Exits the program if a texture can't be loaded
**/
static void	init_textures(t_data *data)
{
	int	x;
	int	y;

	data->textures.im_wall = mlx_xpm_file_to_image(data->mlx.ptr,
			"assets/textures/wall.xpm", &x, &y);
	if (!data->textures.im_wall)
		exit_free(ERR_UNDEFINED, data);
	data->textures.im_floor = mlx_xpm_file_to_image(data->mlx.ptr,
			"assets/textures/floor.xpm", &x, &y);
	if (!data->textures.im_floor)
		exit_free(ERR_UNDEFINED, data);
	data->textures.im_player = mlx_xpm_file_to_image(data->mlx.ptr,
			"assets/textures/player.xpm", &x, &y);
	if (!data->textures.im_player)
		exit_free(ERR_UNDEFINED, data);
}

/**
* @date 21/10/2024
* @file init.c
* @brief Set data's value by parsing filename 
* and using the minilibx
* @exception Exits the program on allocation or input error
**/
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
	return ;
	init_textures(data);
}

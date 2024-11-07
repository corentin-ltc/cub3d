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
	data->controls.settings = false;
	data->controls.w = false;
	data->controls.s = false;
	data->controls.a = false;
	data->controls.d = false;
	data->controls.l_r = 0;
	data->controls.u_d = 0;
	data->player.angle = 0;
	data->player.z_tilt = 0;
	data->player.velocity = 0;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->tmp = NULL;
	data->mlx.last_frame = timenow();
	data->mlx.ptr = NULL;
	data->mlx.win = NULL;
	data->mlx.minimap.img = NULL;
	data->mlx.minimap.width = MINIMAP_FULL_SIZE;
	data->mlx.minimap.height = MINIMAP_FULL_SIZE;
	data->mlx.settings.img = NULL;
	data->mlx.settings.width = MINIMAP_FULL_SIZE / 2;
	data->mlx.settings.height = MINIMAP_FULL_SIZE / 2;
	data->mlx.game.img = NULL;
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
	mlx_get_screen_size(data->mlx.ptr, &data->mlx.window_width, &data->mlx.window_height);
	if (DEBUG)
		data->mlx.window_width /=  2;
	data->mlx.game.width = data->mlx.window_width;
	data->mlx.game.height = data->mlx.window_height;
	data->mlx.win = mlx_new_window(data->mlx.ptr, data->mlx.window_width, data->mlx.window_height, TITLE);
	if (!data->mlx.win)
		exit_free(ERR_MALLOC, data);
}


void	safe_texture(t_data *data, int name, char *path)
{
	data->img[name].img = mlx_xpm_file_to_image(data->mlx.ptr,
			path, &data->img[name].width, &data->img[name].height);
	if (!data->img[name].img)
		exit_free(ERR_UNDEFINED, data);

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

	safe_texture(data, SNIPER, "assets/textures/sniper.xpm");
	safe_texture(data, SCOPE, "assets/textures/scope.xpm");
	safe_texture(data, NORTH, data->N_texture);
	safe_texture(data, SOUTH, data->S_texture);
	safe_texture(data, WEST, data->W_texture);
	safe_texture(data, EAST, data->E_texture);
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
	init_textures(data);
	return ;
}
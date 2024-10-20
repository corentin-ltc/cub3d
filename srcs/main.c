#include "cub3d.h"

/*Sets all data's attribute to their default value*/
static void	init_data(t_data *data)
{
	data->angle = 0;
	data->fd = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->player.start_x = 0;
	data->player.start_y = 0;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->tmp = NULL;
}

//todo: check si la map n'a pas de trou
int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data);
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
		exit_error(ERR_FILE_OPEN);
	get_elements(&data);
	get_map(&data);
	show_data(data);
	free_data(&data);
	return (0);
}

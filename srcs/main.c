#include "cub3d.h"

static void	init_data(t_data *data, int fd)
{
	data->angle = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->N_texture = get_value_by_identifier(fd, "NO ", data);
	data->S_texture = get_value_by_identifier(fd, "SO ", data);
	data->W_texture = get_value_by_identifier(fd, "WE ", data);
	data->E_texture = get_value_by_identifier(fd, "EA ", data);
	data->F_color = get_value_by_identifier(fd, "F ", data);
	data->C_color = get_value_by_identifier(fd, "C ", data);
	// data->map = get_map(fd);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	fd = open_file(argc, argv);
	init_data(&data, fd);
	show_data(data);
	printf("Bye cub :(\n");
	return (0);
}
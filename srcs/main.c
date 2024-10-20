#include "cub3d.h"

/*Parses fd to store it's element inside data*/
/*Stores N,S,W,E textures, F,C colors and the map*/
static void	init_data(t_data *data)
{
	data->angle = 0;
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	fd = open_file(argc, argv);
	init_data(&data);
	show_data(data);
	get_elements(fd, &data);
	show_data(data);
	// data.map = get_map(fd, &data);
	//*****//
	close(fd);
	free_data(&data);
	return (0);
}
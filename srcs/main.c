#include "cub3d.h"

//todo: get player start pos and angle, remove it from the map
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
	check_map(&data);
	show_data(data);
	free_data(&data);
	return (0);
}

/*

		if (is_valid_line(data->tmp) == false)
			exit_free(ERR_MAP_CHAR, data);

*/
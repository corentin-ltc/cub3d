#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data, argv[1]);
	set_hooks(&data);
	mlx_loop(data.mlx.ptr);
	exit_game(&data);
	return (0);
}

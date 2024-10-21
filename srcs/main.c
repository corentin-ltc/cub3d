#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data, argv[1]);
	set_hooks(&data);
	mlx_loop(data.mlx_data.mlx_ptr);
	free_data(&data);
	return (0);
}

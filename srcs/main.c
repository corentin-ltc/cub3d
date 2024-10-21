#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	printf("Checking args\n");
	check_args(argc, argv);
	printf("Initializing data\n");
	init_data(&data, argv[1]);
	printf("Setting hooks\n");
	set_hooks(&data);
	printf("Starting the loop\n");
	mlx_loop(data.mlx_data.mlx_ptr);
	printf("Loop is done\n");
	free_data(&data);
	return (0);
}

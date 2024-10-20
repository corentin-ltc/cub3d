#include "cub3d.h"

void check_args(int argc, char **argv)
{
	int		error_code;
	int		fd;
	char	buffer[1];

	if (argc != 2)
		exit_error(1);
	if (ft_strcmp(".cub", argv[1] + ft_strlen(argv[1]) - 4))
		exit_error(2);
	if (argv[1][0] == '.')
		exit_error(3);
	fd = open(argv[1], O_RDONLY);
	error_code = 0;
	if (fd < 0)
		error_code = 4;
	else if (read(fd, 0, 0) < 0)
		error_code = 5;
	else if (read(fd, buffer, 1) < 1)
		error_code = 6;
	close (fd);
	exit_error(error_code);
}
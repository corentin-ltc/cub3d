#include "cub3d.h"

void	exit_error(int code)
{
	if (code == 0)
		return ;
	if (code == 1)
		ft_putendl_fd("Wrong number of arguments.\nUsage: ./cub3d <map.cub>", 2);
	else if (code == 2)
		ft_putendl_fd("Wrong file extension.\nUsage: ./cub3d <map.cub>", 2);
	else if (code == 3)
		ft_putendl_fd("No filename.\nUsage: ./cub3d <map.cub>", 2);
	else if (code == 4)
		ft_putendl_fd("The file can't be opened.", 2);
	else if (code == 5)
		ft_putendl_fd("The file cannot be read from.", 2);
	else if (code == 6)
		ft_putendl_fd("The file is empty.", 2);
	exit(code);
}
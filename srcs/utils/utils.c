#include "cub3d.h"

static const char	*error_messages[8] = {
	"",
	"Wrong number of arguments.\nUsage: ./cub3d <map.cub>",
	"Wrong file extension.\nUsage: ./cub3d <map.cub>",
	"No filename.\nUsage: ./cub3d <map.cub>",
	"The file can't be opened.",
	"The file cannot be read from.",
	"The file is empty.",
	NULL,
};

void	exit_error(int code)
{
	if (code == 0)
		return ;
	ft_putendl_fd(error_messages[code], 2);
	exit(code);
}

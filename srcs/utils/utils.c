#include "cub3d.h"

static const char	*error_messages[50] = {
	"", // 0
	"Wrong number of arguments.\nUsage: ./cub3d <map.cub>", // 1
	"Wrong file extension.\nUsage: ./cub3d <map.cub>", // 2
	"No filename.\nUsage: ./cub3d <map.cub>", // 3
	"The file can't be opened.", // 4 
	"The file cannot be read from.", // 5
	"The file is empty.", // 6
	"Wrong or missing identifier. (NO,SO,WE,EA,F,C)", // 7
	"Missing value for an identifier.", // 8
	"", // 9
	"Allocation error.", // 10
	NULL,
};

void	exit_error(int code)
{
	if (code == 0)
		return ;
	ft_putendl_fd(error_messages[code], 2);
	exit(code);
}

void	exit_free(int code, t_data *data)
{
	exit_error(code);
	free(data);
}

void	show_data(const t_data data)
{
	printf("N_texture: %s\n", data.N_texture);
	printf("S_texture: %s\n", data.S_texture);
	printf("W_texture: %s\n", data.W_texture);
	printf("E_texture: %s\n", data.E_texture);
	printf("F_color: %s\n", data.F_color);
	printf("C_color: %s\n", data.C_color);
};
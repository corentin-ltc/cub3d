#include "cub3d.h"

static const char	*g_error_messages[50] = {
	"Success!", // 0
	"Wrong number of arguments.\nUsage: ./cub3d <map.cub>", // 1
	"Wrong file extension.\nUsage: ./cub3d <map.cub>", // 2
	"No filename.\nUsage: ./cub3d <map.cub>", // 3
	"The file can't be opened.", // 4 
	"The file cannot be read from.", // 5
	"The file is empty.", // 6
	"Wrong or missing identifier. (NO,SO,WE,EA,F,C, MAP)", // 7
	"Missing value for an identifier.", // 8
	"Bad identifier value.", // 9
	"Allocation error.", // 10
	"The map is missing.", // 11
	"The map has an invalid character.", // 12
	"The map isn't surrounded by walls.", // 13
	"The map must have one and only one player.", // 14
	NULL,
};

/*Exits the shell with the error code <code>*/
/*Prints the corresponding error message*/
void	exit_error(int code)
{
	if (code == 0)
		return ;
	ft_putendl_fd(g_error_messages[code], 2);
	exit(code);
}

/*exit_error() but it also frees data struct.*/
void	exit_free(int code, t_data *data)
{
	free_data(data);
	exit_error(code);
}

void	free_data(t_data *data)
{
	if (data->N_texture != NULL)
		free(data->N_texture);
	if (data->S_texture != NULL)
		free(data->S_texture);
	if (data->W_texture != NULL)
		free(data->W_texture);
	if (data->E_texture != NULL)
		free(data->E_texture);
	if (data->F_color != NULL)
		free(data->F_color);
	if (data->C_color != NULL)
		free(data->C_color);
	if (data->map != NULL)
		free_2d((void *)data->map, 0);
	if (data->tmp != NULL)
		free(data->tmp);
	if (data->fd > 0)
		close(data->fd);
}
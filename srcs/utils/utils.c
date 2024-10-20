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

/*Prints the struct's attributes line by line.*/
void	show_data(const t_data data)
{
	printf("N_texture: %s\n", data.N_texture);
	printf("S_texture: %s\n", data.S_texture);
	printf("W_texture: %s\n", data.W_texture);
	printf("E_texture: %s\n", data.E_texture);
	printf("F_color: %s\n", data.F_color);
	printf("C_color: %s\n", data.C_color);
	ft_putarr(data.map);
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
		free(data->map);
	if (data->tmp != NULL)
		free(data->tmp);
	if (data->fd > 0)
		close(data->fd);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

#include "cub3d.h"

/*Error messages used with defines to get the correct index*/
static const char	*g_error_messages[50] = {
	"Success!",
	"Wrong number of arguments.\nUsage: ./cub3d <map.cub>",
	"Wrong file extension.\nUsage: ./cub3d <map.cub>",
	"No filename.\nUsage: ./cub3d <map.cub>",
	"The file can't be opened.",
	"The file cannot be read from.",
	"The file is empty.",
	"Wrong or missing identifier. (NO,SO,WE,EA,F,C, MAP)",
	"Missing value for an identifier.",
	"Bad identifier value.",
	"Allocation error.",
	"The map is missing.",
	"The map has an invalid character.",
	"The map isn't surrounded by walls.",
	"The map must have one and only one player.",
	NULL,
};

/*Exits the shell with the error code <code>*/
/*Prints the corresponding error message*/
void	exit_error(int code)
{
	if (code == 0)
		return;
	ft_putendl_fd(g_error_messages[code], 2);
	exit(code);
}

/*exit_error() but it also frees data struct.*/
void	exit_free(int code, t_data *data)
{
	free_data(data);
	exit_error(code);
}

/*Frees the pointer which aren't pointing to NULL*/
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

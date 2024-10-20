#include "cub3d.h"

/*Returns argv[1]'s fd or exit the program if the input is wrong*/
int open_file(int argc, char **argv)
{
	int		error_code;
	int		fd;
	char	buffer[1];

	if (argc != 2)
		exit_error(ERR_ARG_COUNT);
	if (ft_strcmp(".cub", argv[1] + ft_strlen(argv[1]) - 4))
		exit_error(ERR_ARG_EXT);
	if (argv[1][0] == '.')
		exit_error(ERR_ARG_NAME);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_FILE_OPEN);
	error_code = 0;
	if (read(fd, 0, 0) < 0)
		error_code = ERR_FILE_READ;
	else if (read(fd, buffer, 1) < 1)
		error_code = ERR_FILE_EMPTY;
	close(fd);
	exit_error(error_code);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_FILE_OPEN);
	return (fd);
}

static void	get_element(char **elem, int fd, t_data *data)
{
	size_t	start;
	size_t	i;

	i = 0;
	while (ft_isalpha(data->tmp[i]))
		i++;
	while (ft_isspace(data->tmp[i]))
		i++;
	if (data->tmp[i] == '\0')
		exit_free(ERR_VALUE_MISSING, data);
	start = i;
	while (data->tmp[i] && data->tmp[i] != '\n' && !ft_isspace(data->tmp[i]))
		i++;
	while (ft_isspace(data->tmp[i]))
		i++;
	if (data->tmp[i] != '\0')
		exit_free(ERR_VALUE_ERROR, data);
	*elem = ft_strdup(data->tmp);
	return ;
	fd++;
	data++;
}

void	get_elements(int fd, t_data *data)
{
	while (!data->N_texture || !data->S_texture || !data->E_texture
		|| !data->W_texture || !data->F_color || !data->C_color)
	{
		data->tmp = skip_empty_lines(fd);
		if (data->tmp == NULL)
			exit_free(ERR_ID_MISSING, data);
		if (ft_strncmp(data->tmp, "NO", 2) == 0)
			get_element(&data->N_texture, fd, data);
		else if (ft_strncmp(data->tmp, "SO", 2) == 0)
			get_element(&data->S_texture, fd, data);
		else if (ft_strncmp(data->tmp, "WE", 2) == 0)
			get_element(&data->W_texture, fd, data);
		else if (ft_strncmp(data->tmp, "EA", 2) == 0)
			get_element(&data->E_texture, fd, data);
		else if (ft_strncmp(data->tmp, "F", 1) == 0)
			get_element(&data->F_color, fd, data);
		else if (ft_strncmp(data->tmp, "C", 1) == 0)
			get_element(&data->C_color, fd, data);
		else
			exit_free(ERR_ID_MISSING, data);
		free(data->tmp);
		data->tmp = NULL;
	}
	free(data->tmp);
	data->tmp = NULL;
}

/*Returns the value found on the identifier line*/
/*Puts the fd cursor after the correct line*/
/*Exits the program on error*/
// char	*get_value_by_identifier(int fd, const char *id, t_data *data)
// {
// 	if (data->tmp[ft_strlen(id) + 1] == '\0')
// 		exit_free(ERR_VALUE_MISSING, data);
// 	value = ft_strdup(data->tmp + ft_strlen(id));
// 	free(data->tmp);
// 	data->tmp = NULL;
// 	if (!value)
// 		exit_free(ERR_MALLOC, data);
// 	return (value);
// }

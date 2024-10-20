#include "cub3d.h"

/*exits the program if the given input is wrong*/
/*@file parsing.c */
void	check_args(int argc, char **argv)
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
}

/*retrieves the value of the current line and make <elem> points to it*/
/*exits the program on error (invalid value or allocation)*/
/* @param[in] elem The number of words to read.*/
/*@return "prout"*/
static void	get_element(char **elem, t_data *data)
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
	*elem = ft_strdup(data->tmp + start);
	if (!*elem)
		exit_free(ERR_MALLOC, data);
}

/*Parses fd to store it's element inside data*/
/*Stores N,S,W,E textures and F,C colors*/
/*Puts the fd cursor after the last element*/
void	get_elements(t_data *data)
{
	while (!data->N_texture || !data->S_texture || !data->E_texture
		|| !data->W_texture || !data->F_color || !data->C_color)
	{
		data->tmp = skip_empty_lines(data->fd);
		if (data->tmp == NULL)
			exit_free(ERR_ID_MISSING, data);
		if (ft_strncmp(data->tmp, "NO", 2) == 0)
			get_element(&data->N_texture, data);
		else if (ft_strncmp(data->tmp, "SO", 2) == 0)
			get_element(&data->S_texture, data);
		else if (ft_strncmp(data->tmp, "WE", 2) == 0)
			get_element(&data->W_texture, data);
		else if (ft_strncmp(data->tmp, "EA", 2) == 0)
			get_element(&data->E_texture, data);
		else if (ft_strncmp(data->tmp, "F", 1) == 0)
			get_element(&data->F_color, data);
		else if (ft_strncmp(data->tmp, "C", 1) == 0)
			get_element(&data->C_color, data);
		else
			exit_free(ERR_ID_MISSING, data);
		free(data->tmp);
		data->tmp = NULL;
	}
	free(data->tmp);
	data->tmp = NULL;
}

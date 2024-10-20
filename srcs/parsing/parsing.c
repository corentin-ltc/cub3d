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
/*Returns the value found on the identifier line*/
/*Puts the fd cursor after the correct line*/
/*Exits the program on error*/
char	*get_value_by_identifier(int fd, const char *id, t_data *data)
{
	char	*value;

	data->tmp = get_next_line(fd);
	while (data->tmp && data->tmp[0] == '\n')
	{
		free(data->tmp);
		data->tmp = get_next_line(fd);
	}
	if (data->tmp == NULL || ft_strncmp(id, data->tmp, ft_strlen(id)))
		exit_free(ERR_ID_MISSING, data);
	if (data->tmp[ft_strlen(id) + 1] == '\0')
		exit_free(ERR_VALUE_MISSING, data);
	value = ft_strdup(data->tmp + ft_strlen(id));
	free(data->tmp);
	data->tmp = NULL;
	if (!value)
		exit_free(ERR_MALLOC, data);
	return (value);
}

static bool	is_valid_line(char *line)
{
	size_t	i;
	bool	is_valid;

	i = 0;
	is_valid = true;
	while (line[i] && is_valid)
	{
		is_valid = false;
		if (ft_isspace(line[i]) || line[i] == '\n')
			is_valid = true;
		if (line[i] == '0' || line[i] == '1')
			is_valid = true;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			is_valid = true;
		i++;
	}
	return (is_valid);
}

char	**get_map(int fd, t_data *data)
{
	char	**map;
	t_list	*lines;

	map = NULL;
	data->tmp = get_next_line(fd);
	while  (data->tmp && data->tmp[0] == '\n')
	{
		free(data->tmp);
		data->tmp = get_next_line(fd);
	}
	if (data->tmp == NULL)
		exit_free(ERR_MAP_MISSING, data);
	lines = NULL;
	while (data->tmp)
	{
		if (is_valid_line(data->tmp) == false || data->tmp[0] == '\n')
			exit_free(ERR_MAP_CHAR, data);
		data->tmp = get_next_line(fd);
	}
	return (map);
}

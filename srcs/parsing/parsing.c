#include "cub3d.h"

int open_file(int argc, char **argv)
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
	if (fd < 0)
		exit_error(4);
	error_code = 0;
	if (read(fd, 0, 0) < 0)
		error_code = 5;
	else if (read(fd, buffer, 1) < 1)
		error_code = 6;
	close(fd);
	exit_error(error_code);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(4);
	return (fd);
}

char	*get_value_by_identifier(int fd, const char *id, t_data *data)
{
	char	*value;
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL || ft_strncmp(id, line, ft_strlen(id)))
	{
		if (line)
			free(line);
		exit_free(7, data); // exit on wrong order or missing id;
	}
	if (line[ft_strlen(id) + 1] == '\0')
	{
		free(line);
		exit_free(8, data); // exit on missing value;
	}
	value = ft_strdup(line + ft_strlen(id) + 1);
	free(line);
	if (!value)
		exit_free(10, data); // malloc error
	return (value);
}

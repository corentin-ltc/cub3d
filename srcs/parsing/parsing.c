#include "cub3d.h"

/*Returns argv[1]'s fd or exit the program if the input is wrong*/
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
/*Returns the value found on the identifier line*/
/*Puts the fd cursor after the correct line*/
/*Exits the program on error*/
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
		exit_free(7, data);
	}
	if (line[ft_strlen(id) + 1] == '\0')
	{
		free(line);
		exit_free(8, data);
	}
	value = ft_strdup(line + ft_strlen(id));
	free(line);
	if (!value)
		exit_free(10, data);
	return (value);
}

char	**get_map(int fd, t_data *data)
{
	char	**map;
	char	*line;

	line = get_next_line(fd);
	map = NULL;
	while  (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	printf("Start of the map :%s\n", line);
	if (line == NULL)
		exit_free(0, data);
	return (map);
}

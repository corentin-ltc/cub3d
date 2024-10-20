#include "cub3d.h"

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
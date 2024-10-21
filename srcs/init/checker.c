#include "cub3d.h"

/*exits the program if the given input is wrong*/
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

static bool	has_hole(char **map, size_t y)
{
	size_t	x;

	x = 0;
	while (map[y][x])
	{
		if (map[y][x] != WALL && map[y][x] != SPACE)
		{
			if (y == 0 || x == 0 || map[y + 1] == NULL || map[y][x + 1] == '\0')
				return (true);
			if (map[y - 1][x] == SPACE || map[y + 1][x] == SPACE)
				return (true);
			if (map[y][x - 1] == SPACE || map[y][x + 1] == SPACE)
				return (true);
		}
		x++;
	}
	return (false);
}

static bool	has_invalid_char(char *line)
{
	size_t	i;
	bool	has_char;

	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	i = 0;
	while (line[i])
	{
		has_char = false;
		if (ft_isspace(line[i]))
			has_char = true;
		if (line[i] == '0' || line[i] == '1' || line[i] == 'W')
			has_char = true;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E')
			has_char = true;
		if (has_char == false)
			return (true);
		i++;
	}
	return (false);
}

static bool	has_player(t_data *data, size_t y)
{
	size_t	x;

	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == 'N')
			data->player.angle = 0;
		else if (data->map[y][x] == 'E')
			data->player.angle = 90;
		else if (data->map[y][x] == 'S')
			data->player.angle = 180;
		else if (data->map[y][x] == 'W')
			data->player.angle = 270;
		if (data->player.angle != -42)
		{
			data->player.start.x = x;
			data->player.start.y = y;
			data->player.pos.x = x;
			data->player.pos.y = y;
			return (true);
		}
		x++;
	}
	return (false);
}

void	check_map(t_data *data)
{
	size_t	y;
	size_t	player_count;

	y = 0;
	player_count = 0;
	while (data->map[y])
	{
		if (has_invalid_char(data->map[y]))
			exit_free(ERR_MAP_CHAR, data);
		if (has_hole(data->map, y))
			exit_free(ERR_MAP_WALL, data);
		player_count += has_player(data, y);
		y++;
	}
	if (player_count < 1 || 1 < player_count )
		exit_free(ERR_MAP_PLAYER, data);
}
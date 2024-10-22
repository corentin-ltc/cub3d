#include "cub3d.h"

/**
* @date 21/10/2024
* @file checker.c
* @brief Check if the arguments are a single openable .cub file
* @example file.cub -> true if can be opened, file.txt -> false
* @exception Exits the program
**/
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

/**
* @date 21/10/2024
* @file checker.c
* @brief Checks if a row of the map has a hole
* @details The row has a hole if a floor cell (0) is next to a void (space or NULL)
**/
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

/**
* @date 21/10/2024
* @file checker.c
* @brief Checks if a row of the map has an invalid char
* @details Anything else than {0,1,N,E,S,W,space} is an invalid char
**/
static bool	has_invalid_char(char *line)
{
	size_t	i;
	bool	has_char;
	bool	only_spaces;

	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	only_spaces = true;
	i = 0;
	while (line[i])
	{
		has_char = false;
		if (line[i] == '0' || line[i] == '1' || line[i] == 'W')
			has_char = true;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E')
			has_char = true;
		if (has_char)
			only_spaces = false;
		if (has_char == false && !ft_isspace(line[i]))
			return (true);
		i++;
	}
	return (only_spaces);
}

/*Returns true if the line has a player and sets the data accordingly*/
/**
* @date 21/10/2024
* @file checker.c
* @brief Checks if a row of the map has a player char (N,E,S,W)
* @note Also sets t_player in t_data accordingly
**/
static bool	has_player(t_data *data, size_t y)
{
	size_t	x;

	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == 'N' || data->map[y][x] == 'E'
			|| data->map[y][x] == 'S' || data->map[y][x] == 'W')
		{
			data->player.angle = data->map[y][x];
			data->map[y][x] = '0';
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

/**
* @date 21/10/2024
* @file checker.c
* @brief Checks the map for invalid chars, holes and player count
* @exception Exits the program if the map is invalid
**/
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
	if (player_count < 1 || 1 < player_count)
		exit_free(ERR_MAP_PLAYER, data);
}

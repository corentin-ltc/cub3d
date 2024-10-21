#include "cub3d.h"

static bool	is_valid_line(char *line)
{
	size_t	i;
	bool	has_char;

	if (line[0] == '\0' || line[0] == '\n')
		return (false);
	i = 0;
	has_char = true;
	while (line[i] && has_char)
	{
		has_char = false;
		if (ft_isspace(line[i]))
			has_char = true;
		if (line[i] == '0' || line[i] == '1' || line[i] == 'W')
			has_char = true;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E')
			has_char = true;
		i++;
	}
	return (has_char);
}

void	get_map_from_lines(t_list *lines, size_t largest, t_data *data)
{
	size_t	player_count;
	size_t	i;

	data->map = calloc(ft_lstsize(lines) + 1, sizeof(char *));
	i = 0;
	player_count = 0;
	while (lines)
	{
		data->map[i] = calloc(largest + 1, sizeof(char));
		if (!data->map[i])
		{
			ft_lstclear(&lines, free);
			exit_free(ERR_MALLOC, data);
		}
		if (ft_lsttos(lines)[ft_strlen(lines->content) - 1] == '\n')
			ft_lsttos(lines)[ft_strlen(lines->content) - 1] = '\0';
		ft_strcat(data->map[i], lines->content);
		if (ft_strchr(data->map[i], 'W') || ft_strchr(data->map[i], 'N')
			|| ft_strchr(data->map[i], 'E') || ft_strchr(data->map[i], 'S'))
			player_count++;
		i++;
		lines = lines->next;
	}
	if (player_count != 1)
		exit_free(ERR_MAP_PLAYER, data);
}

void	get_map(t_data *data)
{
	t_list	*lines;
	t_list	*new;
	size_t	largest;

	data->tmp = skip_empty_lines(data->fd);
	if (data->tmp == NULL)
		exit_free(ERR_MAP_MISSING, data);
	lines = NULL;
	largest = 0;
	while (data->tmp)
	{
		if (is_valid_line(data->tmp) == false)
			exit_free(ERR_MAP_CHAR, data);
		if (ft_strlen(data->tmp) > largest)
			largest = ft_strlen(data->tmp);
		new = ft_lstnew(data->tmp);
		if (!new)
		{
			ft_lstclear(&lines, free);
			exit_free(ERR_MALLOC, data);
		}
		ft_lstadd_back(&lines, new);
		data->tmp = get_next_line(data->fd);
	}
	get_map_from_lines(lines, largest, data);
}

bool	is_valid_map(char **map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		// printf("Current line :%s\n", map[y]);
		while (map[y][x])
		{
			if (map[y][x] != WALL && map[y][x] != SPACE)
			{
				// printf("Current char :%c\n", map[y][x]);
				if (y == 0 || x == 0 || map[y + 1] == NULL || map[x + 1] == NULL)
					return (false);
				if (map[y - 1][x] == SPACE || map[y + 1][x] == SPACE)
					return (false);
				if (map[y][x - 1] == SPACE || map[y][x + 1] == SPACE)
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

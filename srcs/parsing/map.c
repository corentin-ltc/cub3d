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

void	get_map_from_lines(t_list *lines, size_t largest, t_data *data)
{
	//todo: check s'il y a bien un et un seul joueur
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
		if (is_valid_line(data->tmp) == false || data->tmp[0] == '\n')
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

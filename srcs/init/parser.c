#include "cub3d.h"

/*Retrieves the value of the current line and make <elem> points to it*/
/*Exits the program on error (invalid value or allocation)*/
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

/*Transforms the linked list given as argument into a map stored in data*/
static void	get_map_from_lines(t_list *lines, size_t largest, t_data *data)
{
	size_t	i;

	data->map = calloc(ft_lstsize(lines) + 1, sizeof(char *));
	if (!data->map)
	{
		ft_lstclear(&lines, free);
		exit_free(ERR_MALLOC, data);
	}
	i = 0;
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
		i++;
		lines = lines->next;
	}
}

/*Reads data->in_fd and parses the map inside data->map*/
/*Exits the program on wrong map*/
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
	ft_lstclear(&lines, free);
	close(data->fd);
}

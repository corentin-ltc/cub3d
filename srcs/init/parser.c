/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbellila <nbellila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:27:58 by nbellila          #+#    #+#             */
/*   Updated: 2024/11/26 18:27:58 by nbellila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @date 21/10/2024
* @file parser.c
* @brief Retrieves the value of the current line and make <elem> points to it
* @exception Exits the program on error (invalid value or allocation)
**/
static void	get_element(char **elem, t_data *data)
{
	size_t	start;
	size_t	end;
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
	end = i;
	while (ft_isspace(data->tmp[i]))
		i++;
	if (data->tmp[i] != '\0')
		exit_free(ERR_VALUE_ERROR, data);
	*elem = ft_substr(data->tmp, start, end - start);
	if (!*elem)
		exit_free(ERR_MALLOC, data);
}

/**
* @date 21/10/2024
* @file parser.c
* @brief Parses fd to store its element inside data
* @details Stores N,S,W,E textures and F,C colors
* Puts the fd cursor after the last element
* @exception Exits the program if an element is missing
**/
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

/**
* @date 21/10/2024
* @file parser.c
* @brief Transforms the linked list given as argument into a map stored in data
* @param largest Size of the widest line,
* each row will be allocated that much memory
* @note Also removes the newline char from each line
* @exception Exits the program on allocation error
**/
static void	get_map_from_lines(t_list *lines, size_t largest, t_data *data)
{
	size_t	i;

	data->map_height = ft_lstsize(lines);
	data->map = calloc(data->map_height + 1, sizeof(char *));
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

/**
* @date 21/10/2024
* @file parser.c
* @brief Reads data->in_fd and parses the map inside data->map
* @details We store the map inside a linked list to know how much to allocate
* @exception Exits the program on map or allocation error
**/
void	get_map(t_data *data)
{
	t_list	*lines;
	t_list	*new;

	data->tmp = skip_empty_lines(data->fd);
	if (data->tmp == NULL)
		exit_free(ERR_MAP_MISSING, data);
	lines = NULL;
	data->map_width = 0;
	while (data->tmp)
	{
		if (ft_strlen(data->tmp) > data->map_width)
			data->map_width = ft_strlen(data->tmp);
		new = ft_lstnew(data->tmp);
		if (!new)
		{
			ft_lstclear(&lines, free);
			exit_free(ERR_MALLOC, data);
		}
		ft_lstadd_back(&lines, new);
		data->tmp = get_next_line(data->fd);
	}
	get_map_from_lines(lines, data->map_width, data);
	ft_lstclear(&lines, free);
	close(data->fd);
}

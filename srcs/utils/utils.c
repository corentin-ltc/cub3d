/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbellila <nbellila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:45:18 by nbellila          #+#    #+#             */
/*   Updated: 2024/11/26 19:59:31 by nbellila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @date 20/10/2024
* @file utils.c
* @brief Prints the struct's attributes line by line.
**/
void	show_data(const t_data data)
{
	printf("n_texture: %s\n", data.n_texture);
	printf("s_texture: %s\n", data.s_texture);
	printf("w_texture: %s\n", data.w_texture);
	printf("e_texture: %s\n", data.e_texture);
	printf("f_color: %s\n", data.f_color);
	printf("c_color: %s\n", data.c_color);
	ft_putarr(data.map);
}

/**
* @date 20/10/2024
* @file utils.c
* @brief Returns the next non-empty line of a fd
* @note Progress the fd's cursor depending on the buffer used by get_next_line
**/
char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	rgb_convertor(char *str)
{
	char	**rgb;
	int		color;

	rgb = ft_split(str, ",");
	if (!rgb)
		exit_error(ERR_MALLOC);
	color = ft_atoi(rgb[0]);
	color = (color << 8) + ft_atoi(rgb[1]);
	color = (color << 8) + ft_atoi(rgb[2]);
	free_2d((void *)rgb, 3);
	return (color);
}

/**
* @date 20/10/2024
* @file utils.c
* @return time in ms
**/
long long	timenow(void)
{
	struct timeval	tv;
	long long		time_in_ms;	

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	print_pos(t_pos pos, char *name)
{
	printf("%s(%lf,%lf)\n", name, pos.x, pos.y);
}

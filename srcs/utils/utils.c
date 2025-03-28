#include "cub3d.h"

/**
* @date 20/10/2024
* @file utils.c
* @brief Prints the struct's attributes line by line.
**/
void	show_data(const t_data data)
{
	printf("N_texture: %s\n", data.N_texture);
	printf("S_texture: %s\n", data.S_texture);
	printf("W_texture: %s\n", data.W_texture);
	printf("E_texture: %s\n", data.E_texture);
	printf("F_color: %s\n", data.F_color);
	printf("C_color: %s\n", data.C_color);
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
	char **rgb;
	int color;

	rgb = ft_split(str, ",");
	if (!rgb)
		exit_error(ERR_MALLOC);
	color = ft_atoi(rgb[0]);
	color = (color << 8) + ft_atoi(rgb[1]);
	color = (color << 8) + ft_atoi(rgb[2]);
	free_2d((void*)rgb, 3);
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
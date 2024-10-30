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

/* formule pour calculer la distance entre deux points dans le plan cartesien */
double get_distance(t_pos a, t_pos b)
{
	return (sqrt(pow((a.x - b.x), 2) + (pow((a.y - b.y), 2))));
}

t_vector	vector(int x, int y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_pos	pos(double x, double y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

double	nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

void	print_pos(t_pos pos, char *name)
{
	printf("%s(%lf,%lf)\n", name, pos.x, pos.y);
}
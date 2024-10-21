#include "cub3d.h"

/*Prints the struct's attributes line by line.*/
void	show_data(const t_data data)
{
	printf("N_texture: %s\n", data.N_texture);
	printf("S_texture: %s\n", data.S_texture);
	printf("W_texture: %s\n", data.W_texture);
	printf("E_texture: %s\n", data.E_texture);
	printf("F_color: %s\n", data.F_color);
	printf("C_color: %s\n", data.C_color);
	printf("Player: (%d,%d), Angle: %f\n",
		data.player.start.x, data.player.start.y, data.player.angle);
	ft_putarr(data.map);
}

/*Returns the next non-empty line of a fd*/
/*Puts the fd's cursor at the start of the next line*/
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

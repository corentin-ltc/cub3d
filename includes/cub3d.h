#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

/*defines*/

typedef struct	s_pos{
	double	x;
	double	y;
}t_pos;

typedef struct	s_data{
	char	**map;
	char	*N_texture;
	char	*S_texture;
	char	*W_texture;
	char	*E_texture;
	char	*F_color;
	char	*C_color;
	int		angle;
	t_pos	player;
}t_data;

/*parsing*/
int		open_file(int argc, char **argv);
char	*get_value_by_identifier(int fd, const char *identifier, t_data *data);
char	**get_map(int fd, t_data *data);

/*utils*/
void	exit_error(int code);
void	exit_free(int code, t_data *data);
void	show_data(const t_data data);


#endif
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

/*defines*/
#define ERR_ARG_COUNT 1
#define ERR_ARG_EXT 2
#define ERR_ARG_NAME 3
#define ERR_FILE_OPEN 4
#define ERR_FILE_READ 5
#define ERR_FILE_EMPTY 6
#define ERR_ID_MISSING 7
#define ERR_VALUE_MISSING 8
#define ERR_VALUE_ERROR 8
#define ERR_MALLOC 10
#define ERR_MAP_MISSING 11
#define ERR_MAP_CHAR 12
#define ERR_MAP_WALL 13


typedef struct	s_player{
	double	x;
	double	y;
	double	start_x;
	double	start_y;
}t_player;

typedef struct	s_data{
	char		**map;
	char		*N_texture;
	char		*S_texture;
	char		*W_texture;
	char		*E_texture;
	char		*F_color;
	char		*C_color;
	int			angle;
	t_player	player;
	char		*tmp;
}t_data;

/*parsing*/
int		open_file(int argc, char **argv);
void	get_elements(int fd, t_data *data);
char	**get_map(int fd, t_data *data);

/*utils*/
void	exit_error(int code);
void	exit_free(int code, t_data *data);
void	show_data(const t_data data);
void	free_data(t_data *data);
char	*skip_empty_lines(int fd);

#endif
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "libft.h"

/*defines*/
#define FLOOR '0'
#define WALL '1'
#define SPACE ' '

#define ERR_UNDEFINED 0
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
#define ERR_MAP_PLAYER 14

# define WALL '1'
# define SPEED 0.05
# define MINIMAP_X 100
# define MINIMAP_Y 100
# define MINIMAP_SIZE 150
# define BLOCK_SIZE 32
# define PLAYER_SIZE 3
# define TITLE "cub3d"
# define BLUE 0xFF428f77
# define GREEN 0x02D05D
# define RED 0xFFe4bcbf
# define DARK_BLUE 0x143143

typedef struct	s_pos{
	double	x;
	double	y;
}t_pos;

typedef struct	s_coord{
	int		x;
	int		y;
}t_coord;

typedef struct	s_player{
	t_pos	pos;
	t_coord	start;
	double	angle;
}t_player;


typedef struct s_textures
{
	void	*im_wall;
	void	*im_floor;
	void	*im_player;
}			t_textures;

typedef struct s_controls
{

	bool	left_pressed;
	bool	right_pressed;
	bool	up_pressed;
	bool	down_pressed;

}		t_controls;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;
}		t_mlx_data;

typedef struct	s_data{
	
	int			fd;
	char		**map;
	char		*N_texture;
	char		*S_texture;
	char		*W_texture;
	char		*E_texture;
	char		*F_color;
	char		*C_color;
	t_textures	textures;
	t_mlx_data	mlx_data;
	t_player	player;
	t_controls	controls;
	char		*tmp;
}t_data;

/*init*/

void	check_args(int argc, char **argv);
void	init_data(t_data *data, char *filename);
void	check_map(t_data *data);
void	get_elements(t_data *data);
void	get_map(t_data *data);

/*utils*/

void	exit_error(int code);
void	exit_free(int code, t_data *data);
void	show_data(const t_data data);
void	free_data(t_data *data);
char	*skip_empty_lines(int fd);

int		update(t_data *data);
int		exit_game(t_data *data);
bool	is_too_far(double pixel_x, double pixel_y);
long long	timenow(void);
void	set_hooks(t_data *data);
void put_block(double pixel_x, double pixel_y, int color, t_data *data);
void put_player(int color, t_data *data);


#endif
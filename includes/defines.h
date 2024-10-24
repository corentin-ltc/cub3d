#ifndef DEFINES_H
# define DEFINES_H

/*game*/
# define TITLE "cul3d"
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define FPS 30
# define BLOCK_SIZE 32
# define SPEED 0.01
# define MINIMAP_SIZE BLOCK_SIZE * 4
# define MINIMAP_X MINIMAP_SIZE
# define MINIMAP_Y MINIMAP_SIZE
# define PLAYER_SIZE BLOCK_SIZE / 8
/*map*/
#define FLOOR '0'
#define WALL '1'
#define SPACE ' '
/*colors*/
# define BLUE 0xFF428f77
# define GREEN 0x02D05D
# define RED 0xFF0000
# define DARK_BLUE 0x143143
# define WHITE 0xFFFFFF
/*error codes*/
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
/*structs*/
typedef struct	s_pos{
	double	x;
	double	y;
}t_pos;

typedef struct	s_vector{
	int		x;
	int		y;
}t_vector;

typedef struct	s_player{
	t_pos	pos;
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
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
}		t_controls;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_pos	center;
}t_img;

typedef struct s_mlx_data
{
	void		*ptr;
	void		*win;
	t_img		minimap;
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
	t_mlx_data	mlx;
	t_player	player;
	t_controls	controls;
	char		*tmp;
}t_data;

#endif
#ifndef DEFINES_H
# define DEFINES_H

/*game*/
# define TITLE "cul3d"
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define BLOCK_SIZE 32
# define SETTINGS_X WINDOW_WIDTH / 2
# define SETTINGS_Y WINDOW_HEIGHT / 2
/*changeable*/
# define MAX_FPS 90
# define FOV 60
# define MAX_SPEED 0.005
# define ACCELERATION MAX_SPEED / 10
# define ROTATION_SPEED 0.005
# define MINIMAP_SIZE 128
# define RENDER_DISTANCE 4
# define BORDER_WIDTH 1
# define RAY_RATE 0
/*settings*/
# define DEBUG 1
# define SHOW_MAP 1
# define GRID 1
# define LIGHT 1
# define SHOW_RAYS 1
# define HIGHLIGHT_WALLS 1
/*adaptative*/
# define MINIMAP_BLOCK_SIZE abs(MINIMAP_SIZE / RENDER_DISTANCE)
# define MINIMAP_CENTER MINIMAP_SIZE + BORDER_WIDTH
# define MINIMAP_FULL_SIZE (MINIMAP_SIZE + BORDER_WIDTH) * 2
# define PLAYER_SIZE MINIMAP_BLOCK_SIZE / 4
# define FOV_RAD (double)FOV * (PI / 180)
/*cells*/
# define FLOOR '0'
# define WALL '1'
# define SPACE ' '
/*consts*/
# define PI 3.14159265358979323846
# define PX 0.03
# define FPS_INTERVAL 1000
/*colors*/
# define PLAYER_COLOR RED
# define WALL_COLOR DARK_BLUE
# define FLOOR_COLOR BLUE

# define BLUE 0xFF428f77
# define DARK_BLUE 0x143143
# define PURPLE 0xa134eb
# define GREEN 0x02D05D
# define RED 0xFF0000
# define CYAN 0x00FFFF
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GRAY 0x808080
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
	double	velocity;
}t_player;


typedef struct s_textures
{
	void	*im_wall;
	void	*im_floor;
	void	*im_player;
}			t_textures;

typedef struct s_controls
{

	bool	left;
	bool	right;
	bool	up;
	bool	down;
	bool	sprint;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	settings;
	int		l_r;
	int		u_d;
}		t_controls;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_pos	center;
	int		width;
	int		height;
}t_img;

typedef struct s_mlx_data
{
	void		*ptr;
	void		*win;
	int			window_width;
	int			window_height;
	t_img		minimap;
	t_img		game;
	t_img		settings;
	long long	last_frame;
	long long	delta_time;
}		t_mlx_data;

typedef struct	s_data{
	
	int			fd;
	char		**map;
	size_t		map_width;
	size_t		map_height;
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


typedef struct s_ray{
	t_pos		start;
	t_pos		dir;
	t_pos		end;
	t_pos		h_inter;
	t_pos		v_inter;
	t_pos		step;
	double	distance;
	double	angle;
	char	hit;
}t_ray;


typedef enum e_timetype{
	S,
	MS,
	US
}t_timetype;

#endif
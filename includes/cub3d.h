# include <fcntl.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "libft.h"

# define WALL '1'
# define SPEED 0.05
# define MINIMAP_X 60
# define MINIMAP_Y 60
# define MINIMAP_SIZE 60
# define BLOCK_SIZE 32

typedef struct s_textures
{
	void	*im_wall;
	void	*im_floor;
	void	*im_player;
}			t_textures;



typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*mlx_win;
}		t_mlx_data;

typedef struct s_player
{
	double	d_pos_x;
	double	d_pos_y;
	int		start_x;
	int		start_y;
}		t_player;

typedef struct s_controls
{

	bool	left_pressed;
	bool	right_pressed;
	bool	up_pressed;
	bool	down_pressed;

}		t_controls;

typedef struct s_game
{
	char			**map;
	t_textures		*textures;
	t_mlx_data		*mlx_data;
	t_player		*player;
	t_controls		*controls;

}		t_game;

int		update(t_game *game);
void	init_textures(t_mlx_data *mlx_data, t_textures *textures, t_game *game);
int		handle_input(int keycode, t_game *game);
int		exit_game(t_game *game);
bool	is_too_far(double pixel_x, double pixel_y);
void	free_and_exit(t_mlx_data *data, t_game *game);

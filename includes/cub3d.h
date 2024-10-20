# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define SPEED 0.05

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
	double	posx;
	double	posy;
	int		position_y;
	int		position_x;
	bool	left_pressed;
	bool	right_pressed;
	bool	up_pressed;
	bool	down_pressed;

}		t_player;

typedef struct s_game
{
	char			**map;
	t_textures		*textures;
	t_mlx_data		*mlx_data;
	t_player		*player;
}		t_game;

int		update(t_game *game);
void	init_textures(t_mlx_data *mlx_data, t_textures *textures, t_game *game);
int		handle_input(int keycode, t_game *game);
int		exit_game(t_game *game);
void	free_and_exit(t_mlx_data *data, t_game *game);

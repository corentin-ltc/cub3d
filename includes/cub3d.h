#ifndef CUB3D_H
# define CUB3D_H

/*extern libs*/
# include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
/*intern libs*/
# include "../minilibx-linux/mlx.h"
# include "libft.h"
/*structs|defines*/
# include "defines.h"
/*init/init*/
void		init_data(t_data *data, char *filename);
void		set_hooks(t_data *data);
/*init/parser*/
void		get_elements(t_data *data);
void		get_map(t_data *data);
/*init/checker*/
void		check_args(int argc, char **argv);
void		check_map(t_data *data);
/*utils/utils*/
void		show_data(const t_data data);
long long	timenow(void);
char		*skip_empty_lines(int fd);
/*utils/exit*/
void		exit_error(int code);
void		exit_free(int code, t_data *data);
int			exit_game(t_data *data);
void		free_data(t_data *data);
/*raycasting/draw*/
void		put_block(double pixel_x, double pixel_y, int color, t_data *data);
void		put_player(int color, t_data *data);
/*raycasting/minimap*/
/*raycasting/raycasting*/
void		*new_img(t_mlx_data *mlx);
int			update(t_data *data);
bool		is_too_far(double pixel_x, double pixel_y);
void	process_input(t_data *data);

#endif
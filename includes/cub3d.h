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
double		get_distance(t_pos a, t_pos b);
/*utils/exit*/
void		exit_error(int code);
void		exit_free(int code, t_data *data);
int			exit_game(t_data *data);
void		free_data(t_data *data);
/*raycasting/draw*/
void		put_block(t_pos pixel, int color, t_img img);
void		put_player(int color, t_img img);
void	 	put_circle(t_pos pos, int radius, int color, t_img img);
/*raycasting/minimap*/
void		fill_minimap(t_data *data);
/*raycasting/raycasting*/
int			game_loop(t_data *data);
void		process_input(t_data *data);

#endif
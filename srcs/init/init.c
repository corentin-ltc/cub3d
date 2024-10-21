#include "cub3d.h"

/*Sets to-be allocated attributes to NULL to prevent invalid free*/
void	init_data(t_data *data)
{
	data->player.angle = -42;
	data->N_texture = NULL;
	data->S_texture = NULL;
	data->W_texture = NULL;
	data->E_texture = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->map = NULL;
	data->tmp = NULL;
}
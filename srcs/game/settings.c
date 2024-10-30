#include "cub3d.h"

void	show_option(t_data *data, char *str)
{
	static int	y = 20;

	if (!str || !data)
	{
		y = 20;
		return ;
	}
	mlx_string_put(data->mlx.ptr, data->mlx.win, SETTINGS_X + 20, SETTINGS_Y + y, YELLOW, str);
	y += 20;
}

void	show_settings(t_data *data)
{
	show_option(data, "MAP");
	show_option(data, "GRID");
	show_option(data, "LIGHT");
	show_option(data, "RAYS");
	show_option(data, "WALL HIGHLIGTS");
	show_option(NULL, NULL);
}

void	fill_settings(t_data *data)
{
	t_vector	pixel;

	pixel.x = 0;
	while (pixel.x < data->mlx.settings.width)
	{
		pixel.y = 0;
		while (pixel.y < data->mlx.settings.width)
		{
			if (data->controls.settings)
				put_pixel(pixel, data->mlx.settings, GRAY);
			else
				put_pixel(pixel, data->mlx.settings, BLACK);
			pixel.y++;
		}	
		pixel.x++;
	}
}
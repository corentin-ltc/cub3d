#include "cub3d.h"

t_vars	get_bresenham_vars(t_pos a, t_pos b, int isLow)
{
	t_vars	vars;

	vars.dx = b.x - a.x;
	vars.dy = b.y - a.y;
	vars.i = 1;
	if (isLow && vars.dy < 0)
	{
		vars.i = -1;
		vars.dy = -vars.dy;
	}
	if (!isLow && vars.dx < 0)
	{
		vars.i = -1;
		vars.dx = -vars.dx;
	}
	vars.d = 2 * vars.dx - vars.dy;
	return (vars);
}

void	bresenham_low_slope(t_data *data, int color, t_pos a, t_pos b)
{
	t_pos	current;
	t_vars	vars;

	vars = get_bresenham_vars(a, b, 1);
	current = a;
	while (current.x < b.x)
	{
		put_minimap_pixel(vector(current.x, current.y), color, data);
		if (vars.d > 0)
		{
			current.y += vars.i;
			vars.d = vars.d + (2 * (vars.dy - vars.dx));
		}
		else
			vars.d = vars.d + 2 * vars.dy;
		current.x++;
	}
}

void	bresenham_high_slope(t_data *data, int color, t_pos a, t_pos b)
{
	t_pos	current;
	t_vars	vars;

	vars = get_bresenham_vars(a, b, 0);
	current = a;
	while (current.y < b.y)
	{
		put_minimap_pixel(vector(current.x, current.y), color, data);
		if (vars.d > 0)
		{
			current.x += vars.i;
			vars.d = vars.d + (2 * (vars.dx - vars.dy));
		}
		else
			vars.d = vars.d + 2 * vars.dx;
		current.y++;
	}
}
#include "cub3d.h"

void	*new_img(t_mlx_data *mlx)
{
	mlx->img.img = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img.img)
		return (NULL);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel,
			&mlx->img.line_length,
			&mlx->img.endian);
	if (!mlx->img.addr)
		return (NULL);
	return (mlx);
}

static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0)
		return ;
	offset = (y * data->mlx.img.line_length + x
			* (data->mlx.img.bits_per_pixel / 8));
	pixel = data->mlx.img.addr + offset;
	*(unsigned int *)pixel = color;
}

void put_block(double pixel_x, double pixel_y, int color, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < BLOCK_SIZE)
	{
		x = 0;
		while (x < BLOCK_SIZE)
		{
			if (!is_too_far(x + pixel_x, y + pixel_y))
				put_pixel(data, x + pixel_x, y + pixel_y, color);
			x++;
		}
		y++;
	}
}

void put_direction_arrow(t_data *data)
{
	t_pos player;
	t_pos arrow;
	t_pos new;
	double arrow_length;
	double t;
	int	i;

    player.x = (BLOCK_SIZE / 2) + MINIMAP_X;
    player.y = (BLOCK_SIZE / 2) + MINIMAP_Y;
    
    arrow_length = BLOCK_SIZE / 2;
    
    arrow.x = player.x + arrow_length * cos(data->player.angle);
    arrow.y = player.y + arrow_length * sin(data->player.angle);
    
	i = 0;
    while (i < 30) {
        t = (double)i / 30;
        new.x = (int)((1 - t) * player.x + t * arrow.x);
        new.y = (int)((1 - t) * player.y + t * arrow.y);
        put_pixel(data, new.x, new.y, PURPLE);
		i++;
    }
}


void put_player(int color, t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y + i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X + j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			put_pixel(data, (BLOCK_SIZE / 2) + MINIMAP_X - j, (BLOCK_SIZE / 2) + MINIMAP_Y - i, color);
			j++;
		}
		i++;
	}
}
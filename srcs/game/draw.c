#include "cub3d.h"

void	put_pixel(t_vector pixel, t_img img, int color)
{
	char	*img_pixel;
	int		offset;

	if (pixel.x < 0 || pixel.y < 0)
		return ;
	if (pixel.x >= WINDOW_WIDTH || pixel.y >= WINDOW_HEIGHT)
		return ;
	offset = (pixel.y * img.line_length + pixel.x * (img.bits_per_pixel / 8));
	img_pixel = img.addr + offset;
	*(unsigned int *)img_pixel = color;
}

void    put_block(t_data *data, t_vector cell)
{
    t_vector    pixel;
    t_vector    i;
    
    i.y = 0;
    while (i.y < BLOCK_SIZE)
    {
        i.x = -1;
        while (++i.x < BLOCK_SIZE)
        {
            pixel.x = (cell.x * BLOCK_SIZE) - (data->player.pos.x * BLOCK_SIZE) + MINIMAP_X + i.x;
            pixel.y = (cell.y * BLOCK_SIZE) - (data->player.pos.y * BLOCK_SIZE) + MINIMAP_Y + i.y;
			if (get_distance(pos(pixel.x, pixel.y), pos(MINIMAP_X, MINIMAP_Y)) > MINIMAP_SIZE)
				continue ;
            if (i.x == 0 || i.y == 0)
                put_pixel(pixel, data->mlx.minimap, WHITE);
            else if (data->map[cell.y][cell.x] == WALL)
                put_pixel(pixel, data->mlx.minimap, DARK_BLUE);
            else if (data->map[cell.y][cell.x] == FLOOR)
                put_pixel(pixel, data->mlx.minimap, BLUE);
        }
        i.y++;
    }
}

void    put_player(t_data *data)
{
    t_vector    cell;
    t_vector    pixel;

    cell.y = -(PLAYER_SIZE / 2);
	while (cell.y <= PLAYER_SIZE / 2)
	{
		cell.x = -(PLAYER_SIZE / 2);
		while (cell.x <= PLAYER_SIZE / 2)
		{
            pixel.x = (MINIMAP_SIZE) + cell.x;
            pixel.y = (MINIMAP_SIZE) + cell.y;
            put_pixel(pixel, data->mlx.minimap, RED);
			cell.x++;
		}
		cell.y++;
	}
}

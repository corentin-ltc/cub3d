#include "cub3d.h"

static void	put_border(t_data *data)
{
	t_pos i;
	double distance;

	i.y = 0;
	while (i.y < (MINIMAP_CENTER) * 2)
	{
		i.x = 0;
		while (i.x < (MINIMAP_CENTER) * 2)
		{
			distance = get_distance(i, pos(MINIMAP_CENTER, MINIMAP_CENTER));
			if (distance > MINIMAP_SIZE && distance < BORDER_WIDTH + MINIMAP_SIZE)
				put_pixel(vector((int) i.x, (int)i.y), data->mlx.minimap, WHITE);
			i.x++;
		}
		i.y++;
	}	
}

void    fill_minimap(t_data *data)
{
    t_vector    cell;

	cell.y = 0;
	if (data->player.pos.y > RENDER_DISTANCE)
		cell.y = (int)data->player.pos.y - RENDER_DISTANCE;
    while (cell.y < data->player.pos.y + RENDER_DISTANCE && data->map[cell.y])
    {
		cell.x = 0;
		if (data->player.pos.x > RENDER_DISTANCE)
			cell.x = (int)data->player.pos.x - RENDER_DISTANCE;
        while (cell.x < data->player.pos.x + RENDER_DISTANCE && data->map[cell.y][cell.x])
        {
            put_block(data, cell);
            cell.x++;
        }
        cell.y++;
    }
	put_border(data);
	put_cube(pos(data->player.pos.x * MINIMAP_BLOCK_SIZE, data->player.pos.y * MINIMAP_BLOCK_SIZE), PLAYER_SIZE, RED, data);
}
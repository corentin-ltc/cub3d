#include "cub3d.h"

static void    map_foreach(t_data *data, void (*f)(t_data *, t_vector))
{
    t_vector    cell;

    cell.y = 0;
    while (data->map[cell.y])
    {
        cell.x = 0;
        while (data->map[cell.y][cell.x])
        {
            f(data, cell);
            cell.x++;
        }
        cell.y++;
    }
}

void    fill_minimap(t_data *data)
{
    map_foreach(data, put_block);
    put_player(data);
}
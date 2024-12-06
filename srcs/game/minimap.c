/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tort <cle-tort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:42:08 by nbellila          #+#    #+#             */
/*   Updated: 2024/12/06 09:25:59 by cle-tort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_minimap_border(t_data *data)
{
	t_pos	i;
	double	dist;

	i.y = 0;
	while (i.y < (MINIMAP_CENTER) * 2)
	{
		i.x = 0;
		while (i.x < (MINIMAP_CENTER) * 2)
		{
			dist = get_dist(i, pos(MINIMAP_CENTER, MINIMAP_CENTER));
			if (dist > MINIMAP_SIZE && dist < BORDER_WIDTH + MINIMAP_SIZE)
				put_pixel(vector((int) i.x, (int)i.y), data->mlx.game, WHITE);
			i.x++;
		}
		i.y++;
	}
}

static void	put_minimap_block(t_data *data, t_vector cell)
{
	t_vector	pixel;
	t_vector	i;

	i.y = GRID;
	while (i.y < MINIMAP_BLOCK_SIZE)
	{
		i.x = GRID;
		while (i.x < MINIMAP_BLOCK_SIZE)
		{
			pixel.x = (cell.x * MINIMAP_BLOCK_SIZE) + i.x;
			pixel.y = (cell.y * MINIMAP_BLOCK_SIZE) + i.y;
			if (data->map[cell.y][cell.x] == WALL)
				put_minimap_pixel(pixel, WALL_COLOR, data);
			else if (data->map[cell.y][cell.x] == FLOOR)
				put_minimap_pixel(pixel, FLOOR_COLOR, data);
			i.x ++;
		}
		i.y++;
	}
}

static void	put_player(t_data *data)
{
	t_pos	player;
	int		color;

	player = pos(data->player.pos.x * MINIMAP_BLOCK_SIZE,
			data->player.pos.y * MINIMAP_BLOCK_SIZE);
	if (LIGHT)
		color = PLAYER_COLOR;
	else
		color = PLAYER_COLOR_LIGHT_OFF;
	put_cube(player, PLAYER_SIZE, color, data);
}

void	draw_minimap(t_data *data)
{
	t_vector	cell;

	cell.y = 0;
	if (data->player.pos.y > RENDER_DISTANCE)
		cell.y = (int)data->player.pos.y - RENDER_DISTANCE;
	while (LIGHT
		&& cell.y < data->player.pos.y + RENDER_DISTANCE && data->map[cell.y])
	{
		cell.x = 0;
		if (data->player.pos.x > RENDER_DISTANCE)
			cell.x = (int)data->player.pos.x - RENDER_DISTANCE;
		while (cell.x < data->player.pos.x + RENDER_DISTANCE
			&& data->map[cell.y][cell.x])
		{
			put_minimap_block(data, cell);
			cell.x++;
		}
		cell.y++;
	}
	put_minimap_border(data);
	put_player(data);
}

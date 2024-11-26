/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbellila <nbellila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:53:46 by nbellila          #+#    #+#             */
/*   Updated: 2024/11/26 19:14:06 by nbellila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_vector pixel, t_img img, int color)
{
	char	*img_pixel;
	int		offset;

	if (pixel.x < 0 || pixel.y < 0)
		return ;
	if (pixel.x >= img.width || pixel.y >= img.height)
		return ;
	offset = (pixel.y * img.line_length + pixel.x * (img.bits_per_pixel / 8));
	img_pixel = img.addr + offset;
	*(unsigned int *)img_pixel = color;
}

void	put_minimap_pixel(t_vector pixel, int color, t_data *data)
{
	double	distance_from_map_center;

	pixel.x = pixel.x - (data->player.pos.x * MINIMAP_BLOCK_SIZE)
		+ (MINIMAP_SIZE);
	pixel.y = pixel.y - (data->player.pos.y * MINIMAP_BLOCK_SIZE)
		+ (MINIMAP_SIZE);
	distance_from_map_center = get_dist(
			pos(pixel.x, pixel.y),
			pos(MINIMAP_CENTER, MINIMAP_CENTER)
			);
	if (distance_from_map_center > MINIMAP_BLOCK_SIZE * RENDER_DISTANCE)
		return ;
	put_pixel(pixel, data->mlx.game, color);
}

void	put_game_pixel(t_vector pixel, int color, t_data *data)
{
	double	distance_from_map_center;

	distance_from_map_center = get_dist(
			pos(pixel.x, pixel.y),
			pos(MINIMAP_CENTER, MINIMAP_CENTER)
			);
	if (SHOW_MAP == false)
		put_pixel(pixel, data->mlx.game, color);
	else if (distance_from_map_center > MINIMAP_BLOCK_SIZE * RENDER_DISTANCE)
		put_pixel(pixel, data->mlx.game, color);
}

void	put_cube(t_pos center, int size, int color, t_data *data)
{
	int	x;
	int	y;

	y = -size >> 1;
	while (y <= size >> 1)
	{
		x = -size >> 1;
		while (x <= size >> 1)
		{
			put_minimap_pixel(vector(center.x + x, center.y + y), color, data);
			x++;
		}
		y++;
	}
}

void	put_ray(t_ray ray, int color, t_data *data)
{
	int			i;
	t_vector	pixel;

	i = 0;
	while (i < ray.distance * MINIMAP_BLOCK_SIZE && i < MINIMAP_SIZE)
	{
		ray.dir = pos(cos(ray.angle) * i, sin(ray.angle) * i);
		pixel = vector(
				((ray.start.x * MINIMAP_BLOCK_SIZE) + ray.dir.x),
				((ray.start.y * MINIMAP_BLOCK_SIZE) + ray.dir.y)
				);
		if (i && RAY_RATE != 0 && i % RAY_RATE == 0)
			put_minimap_pixel(pixel, color, data);
		i++;
	}
}

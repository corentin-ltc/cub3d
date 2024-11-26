/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbellila <nbellila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:45:40 by nbellila          #+#    #+#             */
/*   Updated: 2024/11/26 19:14:06 by nbellila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* formule pour calculer la distance entre deux points dans le plan cartesien */
double	get_dist(t_pos a, t_pos b)
{
	return (sqrt(pow((a.x - b.x), 2) + (pow((a.y - b.y), 2))));
}

t_vector	vector(int x, int y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_pos	pos(double x, double y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_pos	scaled_pos(t_pos tmp)
{
	return (pos(tmp.x * BLOCK_SIZE, tmp.y * BLOCK_SIZE));
}

double	nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

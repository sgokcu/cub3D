/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 15:29:30 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_put_pixel(t_img *img, int x, int y, t_color color)
{
	img->data[x + (img->size_line * y)] = color;
}

void	ceiling_floor_drawing(t_cub3D *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i >= 0 && i < WIDTH)
	{
		j = 0;
		while (j >= 0 && j < HEIGHT)
		{
			if (j <= HEIGHT / 2)
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->ceiling);
			else
				ft_put_pixel(&cub3d->mlx.img, i, j, cub3d->floor);
			j++;
		}
		i++;
	}
}

t_bool	ft_vec2_equ(t_vec2 vec1, t_vec2 vec2)
{
	if (fabs(vec1.x) - fabs(vec2.x) < EPSILON
		&& fabs(vec1.y) - fabs(vec2.y) < EPSILON)
		return (true);
	return (false);
}

float	ft_vec2_dist(t_vec2 point1, t_vec2 point2)
{
	float	dist_x;
	float	dist_y;

	dist_x = fabs(point1.x - point2.x);
	dist_y = fabs(point1.y - point2.y);
	return (sqrtf(powf(dist_x, 2) + powf(dist_y, 2)));
}

float	ft_lerp(float val, float min, float max)
{
	return ((val * (max - min)) + min);
}

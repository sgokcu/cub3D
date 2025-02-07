/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 15:40:41 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_vec2	hit_vert(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	vert_hit_regulator(&ray, start, dir);
	while (ray.x >= 0 && ray.x < cub3d->map.size.x)
	{
		ray.y = ((dir.y / dir.x) * (ray.x - start.x)) + start.y;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_magnitude(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= MAX_RAY_LENGHT)
			break ;
		if (ray.y >= 0 && ray.y < cub3d->map.size.y)
		{
			if (cub3d->p->s_line[(int)(ray.x + ray.offset)
				+ ((int)ray.y * cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		}
		ray.x += ray.step;
	}
	return (g_vec2_null);
}

void	hori_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.y < 0)
	{
		ray->y = (int)start.y;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->y = (int)start.y + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

t_vec2	hit_hori(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, float *dist)
{
	t_raycast	ray;

	hori_hit_regulator(&ray, start, dir);
	while (ray.y > 0 && ray.y < cub3d->map.size.y)
	{
		ray.x = ((dir.x / dir.y) * (ray.y - start.y)) + start.x;
		ray.hit.pos = (t_vec2){.x = ray.x, .y = ray.y};
		*dist = ft_vec2_magnitude(ft_vec2_sub(ray.hit.pos, start));
		if (*dist >= MAX_RAY_LENGHT)
			break ;
		if (ray.x > 0 && ray.x < cub3d->map.size.x)
			if (cub3d->p->s_line[(int)(ray.x) + (((int)ray.y + ray.offset)
					* cub3d->map.size.x)] == '1')
				return (ray.hit.pos);
		ray.y += ray.step;
	}
	return (g_vec2_null);
}

void	raycast(t_cub3D *cub3d, t_vec2 start, t_vec2 dir, t_hit *out)
{
	t_vec2	vert;
	t_vec2	hori;
	float	dist_vert;
	float	dist_hori;

	dist_vert = 0;
	dist_hori = 0;
	vert = hit_vert(cub3d, start, dir, &dist_vert);
	hori = hit_hori(cub3d, start, dir, &dist_hori);
	if (dist_hori <= dist_vert)
	{
		out->pos = hori;
		if ((start.y - hori.y) < 0)
			out->face = north;
		else
			out->face = south;
	}
	else
	{
		out->pos = vert;
		if ((start.x - vert.x) < 0)
			out->face = west;
		else
			out->face = east;
	}
}

void	ray_modify(t_cub3D *cub3d)
{
	int		i;
	float	deg_step;

	i = 0;
	deg_step = -(WIDTH / 2);
	while (i < WIDTH)
	{
		cub3d->coll_deg[i] = ft_rad_to_deg(atan(deg_step / WIDTH));
		raycast(cub3d, cub3d->player.pos, ft_vec2_rot(cub3d->player.dir,
				cub3d->coll_deg[i]),
			&cub3d->collisions[i]);
		deg_step += 1;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/08 14:58:04 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_vec2	ft_vec2_rot(t_vec2 vec, float deg)
{
	t_vec2	res;
	float	rad;

	rad = ft_deg_to_rad(deg);
	res.x = ((vec.x * cos(rad)) - (vec.y * sin(rad)));
	res.y = ((vec.x * sin(rad)) + (vec.y * cos(rad)));
	return (res);
}

t_vec2	ft_vec2_mul(t_vec2 vec, float mul)
{
	t_vec2	vec_res;

	vec_res.x = vec.x * mul;
	vec_res.y = vec.y * mul;
	return (vec_res);
}

t_vec2	ft_vec2_add(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	vec_res;

	vec_res.x = vec1.x + vec2.x;
	vec_res.y = vec1.y + vec2.y;
	return (vec_res);
}

void	player_collision(t_cub3D *cub3d, t_vec2 next_pos)
{
	if (next_pos.x > cub3d->player.pos.x)
	{
		if (cub3d->p->s_line[(int)(next_pos.x + PLAYER_SIZE)
			+ ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
			cub3d->player.pos.x = next_pos.x;
	}
	else
	{
		if (cub3d->p->s_line[(int)(next_pos.x - PLAYER_SIZE)
			+ ((int)cub3d->player.pos.y * cub3d->map.size.x)] != '1')
			cub3d->player.pos.x = next_pos.x;
	}
	if (next_pos.y > cub3d->player.pos.y)
	{
		if (cub3d->p->s_line[(int)cub3d->player.pos.x
				+ ((int)(next_pos.y + PLAYER_SIZE) *cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
	else
	{
		if (cub3d->p->s_line[(int)cub3d->player.pos.x
				+ ((int)(next_pos.y - PLAYER_SIZE) *cub3d->map.size.x)] != '1')
			cub3d->player.pos.y = next_pos.y;
	}
}

void	player_movement(t_cub3D *cub3d, t_vec2 dir)
{
	t_vec2		next_pos;

	next_pos = ft_vec2_add(cub3d->player.pos,
			ft_vec2_mul(dir, cub3d->player.move_speed));
	player_collision(cub3d, next_pos);
}

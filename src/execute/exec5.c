/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 15:35:15 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_camera(t_cub3D *cub3d, t_bool rotate_dir)
{
	cub3d->player.dir = ft_vec2_rot(cub3d->player.dir,
			cub3d->player.camera_speed * rotate_dir);
}

void	player_modify(t_cub3D *cub3d)
{
	t_vec2	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = cub3d->inputs;
	move_dir = (t_vec2){.x = inputs.a_key
		+ inputs.d_key, .y = inputs.w_key + inputs.s_key};
	move_dir = ft_vec2_norm(move_dir);
	move_dir = ft_vec2_rot(move_dir,
			ft_rad_to_deg(-atan2(cub3d->player.dir.x, cub3d->player.dir.y)));
	rotate_dir = inputs.left_key + inputs.right_key;
	rotate_camera(cub3d, rotate_dir);
	player_movement(cub3d, move_dir);
}

void	vert_hit_regulator(t_raycast *ray, t_vec2 start, t_vec2 dir)
{
	if (dir.x < 0)
	{
		ray->x = (int)start.x;
		ray->step = -1;
		ray->offset = -1;
	}
	else
	{
		ray->x = (int)start.x + 1;
		ray->step = 1;
		ray->offset = 0;
	}
}

float	ft_vec2_magnitude(t_vec2 vec)
{
	t_vec2	vec_null;

	vec_null.x = 0;
	vec_null.y = 0;
	return (ft_vec2_dist(vec_null, vec));
}

t_vec2	ft_vec2_sub(t_vec2	vec1, t_vec2 vec2)
{
	t_vec2	vec_res;

	vec_res.x = vec1.x - vec2.x;
	vec_res.y = vec1.y - vec2.y;
	return (vec_res);
}

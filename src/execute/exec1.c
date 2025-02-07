/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 17:02:43 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	ft_rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}

void	init_map(t_cub3D *cub3d)
{
	cub3d->map.size.x = cub3d->p->map_size.x;
	cub3d->map.size.y = cub3d->p->map_size.y;
	cub3d->map.tiles = cub3d->p->s_line;
	if (cub3d->map.tiles == NULL)
	{
		printf("cub3d: MLX Texture Error\n");
		exit(EXIT_FAILURE);
	}
}

void	init_player(t_cub3D *cub3d)
{
	cub3d->player.pos.x = (float)cub3d->p->ch.p_loc.x + 1.5;
	cub3d->player.pos.y = (float)cub3d->p->ch.p_loc.y + 1.5;
	if (cub3d->p->ch.direction == 'S')
		cub3d->player.dir = g_south;
	if (cub3d->p->ch.direction == 'N')
		cub3d->player.dir = g_north;
	if (cub3d->p->ch.direction == 'E')
		cub3d->player.dir = g_east;
	if (cub3d->p->ch.direction == 'W')
		cub3d->player.dir = g_west;
	cub3d->player.move_speed = 0.05;
	cub3d->player.camera_speed = 1;
}

float	ft_deg_to_rad(float deg)
{
	return ((deg / 180) * PI);
}

void	init_win(t_cub3D *cub3d)
{
	if (cub3d->mlx.mlx == NULL)
	{
		printf("cub3d: MLX Error\n");
		exit(EXIT_FAILURE);
	}
	cub3d->mlx.win.height = HEIGHT;
	cub3d->mlx.win.width = WIDTH;
	cub3d->mlx.win.win = mlx_new_window(cub3d->mlx.mlx,
			WIDTH, HEIGHT, "cub3d - game");
	if (cub3d->mlx.win.win == NULL)
	{
		printf("cub3d: MLX Win Error\n");
		exit(EXIT_FAILURE);
	}
	cub3d->mlx.img.img = mlx_new_image(cub3d->mlx.mlx,
			cub3d->mlx.win.width, cub3d->mlx.win.height);
	cub3d->mlx.img.data = (t_color *)mlx_get_data_addr(cub3d->mlx.img.img,
			&cub3d->mlx.img.bits_per_pixel,
			&cub3d->mlx.img.size_line, &cub3d->mlx.img.endian);
	cub3d->mlx.img.size_line /= 4;
}

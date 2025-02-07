/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 18:47:37 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_drawing(t_cub3D *cub3d)
{
	float	line_height;
	float	ray_len;
	int		i;

	i = 0;
	while (i < HEIGHT)
	{
		if (ft_vec2_equ(cub3d->collisions[i].pos, g_vec2_null))
		{
			i++;
			continue ;
		}
		ray_len = ft_vec2_dist(cub3d->collisions[i].pos, cub3d->player.pos);
		line_height = HEIGHT
			/ (ray_len * cos(ft_deg_to_rad(cub3d->coll_deg[i])));
		draw_wall_piece(cub3d, line_height, i, cub3d->collisions[i].face);
		i++;
	}
}

int	modify(void *param)
{
	t_cub3D	*cub3d;

	cub3d = (t_cub3D *)param;
	player_modify(cub3d);
	ray_modify(cub3d);
	ceiling_floor_drawing(cub3d);
	wall_drawing(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	return (0);
}

void	init_2(t_main_parse *parser, t_cub3D *cub3d)
{
	if (parser->ch.direction == 'N')
		cub3d->collisions->face = north;
	else if (parser->ch.direction == 'S')
		cub3d->collisions->face = south;
	else if (parser->ch.direction == 'E')
		cub3d->collisions->face = east;
	else if (parser->ch.direction == 'W')
		cub3d->collisions->face = west;
	cub3d->map.size.x = cub3d->p->map_size.x;
	cub3d->map.size.y = cub3d->p->map_size.y;
}

void	cub3d(char **av)
{
	t_main_parse	parser;
	t_cub3D			cub3d;

	if (!start_parse(av[1], &parser))
	{
		ft_putstr_fd("Parse Error\n", 2);
		free(parser.s_line);
		exit(0);
	}
	init_all(&cub3d, &parser);
	mlx_hook(cub3d.mlx.win.win, \
		KeyPress, (1 << 0), arrange_key_press, &cub3d);
	mlx_hook(cub3d.mlx.win.win, \
		KeyRelease, (1 << 1), arrange_key_release, &cub3d);
	mlx_hook(cub3d.mlx.win.win, \
		Destroy, (1 << 17), ft_exit, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, modify, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
	return ;
}

int	main(int ac, char **av)
{
	if (ac == 2)
		cub3d(av);
	else
		ft_putstr_fd("Invalid argument count\n", 2);
}

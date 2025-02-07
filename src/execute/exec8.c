/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 15:36:52 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	ft_normalize(float val, float min, float max)
{
	if (max == min)
		return (1);
	return ((val - min) / (max - min));
}

float	get_tex_y(t_img *tex, float i, float height)
{
	return (ft_lerp(ft_normalize(i, 0, height), 0, tex->size_line));
}

t_color	*get_tex_data(t_img *tex, float tex_x)
{
	return (tex->data + ((int)ft_lerp(tex_x,
				0, tex->size_line) * tex->size_line));
}

void	draw_face(struct s_draw_hlpr drw)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	data = get_tex_data(drw.tex, drw.tex_x);
	i = 0;
	tex_y = 0;
	full_height = drw.line_height;
	if (drw.line_height > HEIGHT)
		drw.line_height = HEIGHT;
	while (i < drw.line_height)
	{
		if (full_height > HEIGHT)
			tex_y = get_tex_y(drw.tex, i
					+ ((full_height - HEIGHT) / 2), full_height);
		else
			tex_y = get_tex_y(drw.tex, i, drw.line_height);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;
		ft_put_pixel(&drw.cub3d->mlx.img,
			drw.index, i + (HEIGHT - drw.line_height) / 2, data[(int)tex_y]);
		i++;
	}
}

void	draw_wall_piece(t_cub3D *cub3d, float lh, int index, t_face face)
{
	float	pos_x;
	float	pos_y;

	pos_x = cub3d->collisions[index].pos.x;
	pos_y = cub3d->collisions[index].pos.y;
	if (face == south)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_south,
			.line_height = lh, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == west)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_west,
			.line_height = lh, .index = index,
			.tex_x = pos_y - (int)pos_y});
	if (face == north)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_north,
			.line_height = lh, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == east)
		draw_face((struct s_draw_hlpr){.cub3d = cub3d, .tex = &cub3d->tex_east,
			.line_height = lh, .index = index,
			.tex_x = pos_y - (int)pos_y});
}

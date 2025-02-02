/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/29 19:20:14 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_swap_int(int *a, int *b)
{
	if (a == b)
		return ;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void	mirror_tex(t_img *tex)
{
	int	i;
	int	j;

	j = 0;
	while (j < tex->size_line)
	{
		i = 0;
		while (i < tex->line_count / 2)
		{
			ft_swap_int((int *)(&tex->data[j + (i * tex->size_line)].value),
				(int *)(&tex->data[j + ((tex->size_line - i - 1)
						* tex->size_line)].value));
			i++;
		}
		j++;
	}
}

void	rotate_index(t_img *tex)
{
	int	i;
	int	j;

	i = 0;
	while (i < tex->size_line)
	{
		j = i;
		while (j < tex->line_count)
		{
			ft_swap_int((int *)(&(tex->data[j + (tex->size_line * i)].value)),
				(int *)(&(tex->data[i + (tex->line_count * j)].value)));
			j++;
		}
		i++;
	}
}

static void	init_tex(t_cub3D *cub3d, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
			&tex->size_line, &tex->line_count);
	if (tex->img == NULL)
	{
		printf("cub3d: MLX Texture Error\n");
		exit(EXIT_FAILURE);
	}
	tex->data = (t_color *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	tex->size_line /= (tex->bits_per_pixel / 8);
	rotate_index(tex);
}

void	init_all(t_cub3D *cub3d, t_main_parse *parser)
{
	cub3d->p = parser;
	cub3d->inputs = (t_input){0};
	cub3d->mlx.mlx = mlx_init();
	cub3d->floor.blue = parser->f_blue;
	cub3d->floor.red = parser->f_red;
	cub3d->floor.green = parser->f_green;
	cub3d->ceiling.blue = parser->c_blue;
	cub3d->ceiling.red = parser->c_red;
	cub3d->ceiling.green = parser->c_green;
	init_tex(cub3d, &cub3d->tex_west, parser->we_texture_path);
	init_tex(cub3d, &cub3d->tex_east, parser->ea_texture_path);
	init_tex(cub3d, &cub3d->tex_south, parser->so_texture_path);
	init_tex(cub3d, &cub3d->tex_north, parser->no_texture_path);
	mirror_tex(&cub3d->tex_north);
	mirror_tex(&cub3d->tex_east);
	init_win(cub3d);
	init_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win.win,
		cub3d->mlx.img.img, 0, 0);
	mlx_do_key_autorepeatoff(cub3d->mlx.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/08 19:45:17 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_entity_count(t_main_parse *parse)
{
	parse->entity_counts.ea_count = 0;
	parse->entity_counts.we_count = 0;
	parse->entity_counts.no_count = 0;
	parse->entity_counts.so_count = 0;
	parse->entity_counts.f_count = 0;
	parse->entity_counts.c_count = 0;
}

void	clean_newlines(char **map, int i)
{
	char	*temp;

	while (map[i])
	{
		temp = ft_strtrim(map[i], "\n");
		free(map[i]);
		map[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
}

void	f_fill(t_main_parse *prs, int y, int x)
{
	if (y < 0 || x < 0)
		return ;
	if (y >= prs->map_size.y || x >= (int)ft_strlen(prs->cpy_sq_map[0]))
		return ;
	if (prs->cpy_sq_map[y][x] == 32)
		return ;
	prs->cpy_sq_map[y][x] = 32;
	f_fill(prs, y - 1, x);
	f_fill(prs, y + 1, x);
	f_fill(prs, y, x - 1);
	f_fill(prs, y, x + 1);
}

int	flf_check(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != 32)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_extra_horizontally(t_main_parse *parser)
{
	f_fill(parser, parser->ch.p_loc.y + 1, parser->ch.p_loc.x + 1);
	return (flf_check(parser->cpy_sq_map));
}

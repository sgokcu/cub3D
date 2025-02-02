/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/29 19:19:56 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	y_func(char **map, int *max_y)
{
	*max_y = 0;
	while (map[*max_y])
		*max_y += 1;
	return (*max_y);
}

void	allocate_enough(t_main_parse *p, char **map, int max_y, char ***sq)
{
	p->map_size.x = get_max_x(map);
	*sq = malloc(sizeof(char *) * (max_y + 3));
	fill_index(0, p, *sq);
}

void	copy_loop(char **sq, int y, int *i, char **map)
{
	while (map[y - 1][*i - 1])
	{
		sq[y][*i] = map[y - 1][*i - 1];
		*i += 1;
	}
}

void	set_char(t_main_parse *p, char **sq, int y, int *i)
{
	while (*i < (p->map_size.x + 2))
	{
		sq[y][*i] = CHAR;
		*i += 1;
	}
}

char	**cpy_sq_map(char **map, t_main_parse *parser)
{
	int		max_y;
	int		i;
	int		y;
	char	**sq_map;

	if (y_func(map, &max_y) < 3)
		return (NULL);
	allocate_enough(parser, map, max_y, &sq_map);
	y = 1;
	while (map[y - 1])
	{
		i = 1;
		sq_map[y] = malloc(sizeof(char) * (parser->map_size.x + 3));
		sq_map[y][0] = CHAR;
		copy_loop(sq_map, y, &i, map);
		set_char(parser, sq_map, y, &i);
		sq_map[y][i] = '\0';
		y++;
	}
	fill_index(y, parser, sq_map);
	sq_map[y + 1] = NULL;
	parser->map_size.y = y + 1;
	parser->map_size.x += 2;
	return (sq_map);
}

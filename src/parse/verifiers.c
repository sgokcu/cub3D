/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 14:52:47 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_verifier(t_main_parse *parser)
{
	if (parser->entity_counts.c_count == 1
		&& parser->entity_counts.ea_count == 1
		&& parser->entity_counts.f_count == 1
		&& parser->entity_counts.no_count == 1
		&& parser->entity_counts.so_count == 1
		&& parser->entity_counts.we_count == 1)
		return (1);
	return (0);
}

int	entity_validator(t_intptr *ct)
{
	if (ct->ea_count == 1 && ct->we_count == 1
		&& ct->so_count == 1 && ct->no_count == 1
		&& ct->f_count == 1 && ct->c_count == 1)
		return (1);
	return (0);
}

int	component_verifier(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'W'
		|| c == 'E' || c == ' ')
	{
		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			return (2);
		return (1);
	}
	return (0);
}

int	char_checker(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0' || c == '1')
		return (1);
	return (0);
}

int	checker(char **map, int y, int x)
{
	if (y == 0 || x == 0)
		return (0);
	if (!char_checker(map[y][x - 1]))
		return (0);
	if (!char_checker(map[y][x + 1]))
		return (0);
	if (!map[y + 1])
		return (0);
	if (!map[y - 1])
		return (0);
	if (!char_checker(map[y + 1][x]))
		return (0);
	if (!char_checker(map[y - 1][x]))
		return (0);
	return (1);
}

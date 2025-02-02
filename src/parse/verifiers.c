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

int	count_verifier(t_main_parse *parser)
{
	if (parser->entity_counts.C_count == 1
		&& parser->entity_counts.EA_count == 1
		&& parser->entity_counts.F_count == 1
		&& parser->entity_counts.NO_count == 1
		&& parser->entity_counts.SO_count == 1
		&& parser->entity_counts.WE_count == 1)
		return (1);
	return (0);
}

int	entity_validator(t_intptr *ct)
{
	if (ct->EA_count == 1 && ct->WE_count == 1
		&& ct->SO_count == 1 && ct->NO_count == 1
		&& ct->F_count == 1 && ct->C_count == 1)
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

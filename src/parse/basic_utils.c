/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 19:02:23 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	trim_each(char **rgb)
{
	char	*temp;
	int		i;

	i = -1;
	while (++i < 3)
	{
		temp = ft_strdup(rgb[i]);
		free(rgb[i]);
		rgb[i] = ft_strtrim(temp, " ");
		free(temp);
	}
}

int	is_all_digit(char **rgb)
{
	int	i;
	int	x;

	i = -1;
	while (++i < 3)
	{
		x = 0;
		while (rgb[i][x])
		{
			if (!ft_isdigit(rgb[i][x]))
			{
				if (rgb[i][x] == '\n')
					break ;
				return (0);
			}
			x++;
		}
	}
	return (1);
}

int	is_all_rgb_value(t_main_parse *p)
{
	if (p->f_red < 0 || p->f_red > 255
		|| p->f_green < 0 || p->f_green > 255
		|| p->f_blue < 0 || p->f_blue > 255
		|| p->c_red < 0 || p->c_red > 255
		|| p->c_green < 0 || p->c_green > 255
		|| p->c_blue < 0 || p->c_blue > 255)
		return (0);
	return (1);
}

int	get_max_x(char **map)
{
	int	max_value;
	int	y;
	int	x;

	max_value = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (max_value < x)
			max_value = x;
		y++;
	}
	return (max_value);
}

void	single_line(t_main_parse *parser)
{
	char	*temp;
	int		i;

	i = 0;
	while (parser->cpy_sq_map[i])
	{
		temp = parser->s_line;
		parser->s_line = ft_strjoin(parser->s_line, parser->cpy_sq_map[i]);
		free(temp);
		i++;
	}
}

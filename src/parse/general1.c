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

int	fill_rgb_values(t_main_parse *p, char **rgb, char c)
{
	trim_each(rgb);
	if (!is_all_digit(rgb))
		return (0);
	if (c == 'f')
	{
		p->f_red = ft_atoi(rgb[0]);
		p->f_green = ft_atoi(rgb[1]);
		p->f_blue = ft_atoi(rgb[2]);
		return (1);
	}
	p->c_red = ft_atoi(rgb[0]);
	p->c_green = ft_atoi(rgb[1]);
	p->c_blue = ft_atoi(rgb[2]);
	if (!is_all_rgb_value(p))
		return (0);
	return (1);
}

char	*get_nums(char *line, char c)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == c && line[i + 1] == 32)
			break ;
		i++;
	}
	i += 2;
	while (line[i] == 32)
		i++;
	x = i;
	while (line[i] && line[i] != '\n')
		i++;
	return (ft_substr(line, x, i - x));
}

int	check_extra_map_vertical(t_main_parse *parse, int i)
{
	char	*temp;

	while (parse->map[i])
	{
		temp = ft_strtrim(parse->map[i++], " ");
		if (temp[0] == '\n')
		{
			free(temp);
			break ;
		}
		if (!temp[0])
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	while (parse->map[i])
	{
		temp = ft_strtrim(parse->map[i++], " ");
		if (temp[0] != '\n' && temp[0] != 0)
			return (free(temp), 0);
		free(temp);
	}
	return (1);
}

int	invalid_component_check(t_main_parse *parse)
{
	int	i;
	int	j;
	int	f;

	i = -1;
	while (parse->map[++i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			f = component_verifier(parse->map[i][j]);
			if (f == 0)
				return (0);
			else if (f == 2)
			{
				if (parse->ch.p_loc.x != -1 && parse->ch.p_loc.y != -1)
					return (0);
				parse->ch.direction = parse->map[i][j];
				parse->ch.p_loc.x = j;
				parse->ch.p_loc.y = i;
			}
			j++;
		}
	}
	return (1);
}

int	blank_checker(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' ||
				map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				if (!checker(map, y, x))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

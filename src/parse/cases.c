/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 14:52:30 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	north_case(char *line, t_main_parse *parse)
{
	char	**splitted_line;

	if (parse->entity_counts.no_count++ > 0)
		return (0);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[1])
	{
		ft_putstr_fd("Invalid North Case\n", 2);
		free_double_pointer(splitted_line);
		return (0);
	}
	parse->no_texture_path = ft_strdup(splitted_line[1]);
	free_double_pointer(splitted_line);
	return (1);
}

int	south_case(char *line, t_main_parse *parse)
{
	char	**splitted_line;

	if (parse->entity_counts.so_count++ > 0)
		return (0);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[1])
	{
		ft_putstr_fd("Invalid South Case\n", 2);
		free_double_pointer(splitted_line);
		return (0);
	}
	parse->so_texture_path = ft_strdup(splitted_line[1]);
	free_double_pointer(splitted_line);
	return (1);
}

int	west_case(char *line, t_main_parse *parse)
{
	char	**splitted_line;

	if (parse->entity_counts.we_count++ > 0)
		return (0);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[1])
	{
		ft_putstr_fd("Invalid West Case\n", 2);
		free_double_pointer(splitted_line);
		return (0);
	}
	parse->we_texture_path = ft_strdup(splitted_line[1]);
	free_double_pointer(splitted_line);
	return (1);
}

int	east_case(char *line, t_main_parse *parse)
{
	char	**splitted_line;

	if (parse->entity_counts.ea_count++ > 0)
		return (0);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[1])
	{
		ft_putstr_fd("Invalid East Case\n", 2);
		free_double_pointer(splitted_line);
		return (0);
	}
	parse->ea_texture_path = ft_strdup(splitted_line[1]);
	free_double_pointer(splitted_line);
	return (1);
}

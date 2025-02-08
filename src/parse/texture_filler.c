/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/08 14:14:49 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	floor_case(char *line, t_main_parse *parse)
{
	char	**splitted_nums;
	char	*num_set;

	if (parse->entity_counts.f_count++ > 0)
		return (0);
	num_set = get_nums(line, 'F');
	if (!comma_checker(num_set))
		return (free(num_set), 0);
	splitted_nums = ft_split(num_set, ',');
	if (!splitted_nums || !splitted_nums[0]
		|| !splitted_nums[1] || !splitted_nums[2])
	{
		ft_putstr_fd("Invalid Floor Case\n", 2);
		free(num_set);
		free_double_pointer(splitted_nums);
		return (0);
	}
	if (!check_if_allocated(splitted_nums)
		|| !fill_rgb_values(parse, splitted_nums, 'f'))
	{
		free_double_pointer(splitted_nums);
		return (free(num_set), 0);
	}
	free_double_pointer(splitted_nums);
	return (free(num_set), 1);
}

int	ceiling_case(char *line, t_main_parse *parse)
{
	char	**splitted_nums;
	char	*num_set;

	if (parse->entity_counts.c_count++ > 0)
		return (0);
	num_set = get_nums(line, 'C');
	if (!comma_checker(num_set))
		return (free(num_set), 0);
	splitted_nums = ft_split(num_set, ',');
	if (!splitted_nums || !splitted_nums[0]
		|| !splitted_nums[1] || !splitted_nums[2])
	{
		ft_putstr_fd("Invalid Ceiling Case\n", 2);
		free(num_set);
		free_double_pointer(splitted_nums);
		return (0);
	}
	if (!check_if_allocated(splitted_nums)
		|| !fill_rgb_values(parse, splitted_nums, 'c'))
	{
		free_double_pointer(splitted_nums);
		return (free(num_set), 0);
	}
	free_double_pointer(splitted_nums);
	return (free(num_set), 1);
}

void	free_textures(t_main_parse *parser)
{
	if (parser->entity_counts.we_count > 0)
		free(parser->we_texture_path);
	if (parser->entity_counts.no_count > 0)
		free(parser->no_texture_path);
	if (parser->entity_counts.so_count > 0)
		free(parser->so_texture_path);
	if (parser->entity_counts.ea_count > 0)
		free(parser->ea_texture_path);
}

int	determine_type(char *line, t_main_parse *parse)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (north_case(line, parse));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (south_case(line, parse));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (west_case(line, parse));
	else if (line[0] == 'F' && line[1] == ' ')
		return (floor_case(line, parse));
	else if (line[0] == 'C' && line[1] == ' ')
		return (ceiling_case(line, parse));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (east_case(line, parse));
	else if ((line[0] == '1' || line[0] == '0') && !count_verifier(parse))
		return (0);
	return (1);
}

int	fill_textures(t_main_parse *parser)
{
	int		i;
	char	*current_line;

	i = 0;
	while (parser->whole_file[i])
	{
		current_line = ft_strtrim(parser->whole_file[i], "\n  ");
		if (!determine_type(current_line, parser))
		{
			free(current_line);
			return (0);
		}
		free(current_line);
		i++;
	}
	if (entity_validator(&parser->entity_counts))
		return (1);
	free_textures(parser);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 19:36:22 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	free_for_checker(t_main_parse *parser, int flag)
{
	free(parser->file_path);
	free_double_pointer(parser->whole_file);
	if (flag)
		free_textures(parser);
	return (0);
}

int	free_till_cpy(t_main_parse *parser, int flag)
{
	free(parser->file_path);
	free_double_pointer(parser->whole_file);
	free(parser->no_texture_path);
	free(parser->ea_texture_path);
	free(parser->we_texture_path);
	free(parser->so_texture_path);
	free_double_pointer(parser->map);
	if (flag)
		free_double_pointer(parser->cpy_sq_map);
	return (0);
}

int	name_checker_norm(t_main_parse *parser)
{
	if (!file_name_checker(parser->ea_texture_path, ".xpm")
		|| !file_name_checker(parser->we_texture_path, ".xpm")
		|| !file_name_checker(parser->so_texture_path, ".xpm")
		|| !file_name_checker(parser->no_texture_path, ".xpm"))
		return (0);
	return (1);
}

int	basic_checks(t_main_parse *parser_str, char *file_path)
{
	int	fd;

	if (!file_name_checker(file_path, ".cub"))
		return (0);
	parser_str->file_path = ft_strdup(file_path);
	fd = open(parser_str->file_path, O_RDWR);
	if (fd == -1)
	{
		free(parser_str->file_path);
		ft_putstr_fd("File not found\n", 2);
		return (0);
	}
	if (!fill_whole_file(parser_str, fd))
		return (0);
	return (1);
}

int	start_parse(char *file_path, t_main_parse *parser_str)
{
	initialize_struct(parser_str);
	if (!basic_checks(parser_str, file_path))
		return (0);
	if (!fill_textures(parser_str))
		free_for_checker(parser_str, 0);
	if (!name_checker_norm(parser_str))
	{
		free_for_checker(parser_str, 1);
		return (0);
	}
	reset_entity_count(parser_str);
	fill_map(parser_str);
	if (!check_extra_map_vertical(parser_str, 0))
		return (free_till_cpy(parser_str, 0));
	clean_newlines(parser_str->map, 0);
	if (!invalid_component_check(parser_str))
		return (free_till_cpy(parser_str, 0));
	parser_str->cpy_sq_map = cpy_sq_map(parser_str->map, parser_str);
	if (!parser_str->cpy_sq_map)
		return (free_till_cpy(parser_str, 0));
	single_line(parser_str);
	if (!check_extra_horizontally(parser_str)
		|| !blank_checker(parser_str->map))
		return (free_till_cpy(parser_str, 1));
	return (1);
}

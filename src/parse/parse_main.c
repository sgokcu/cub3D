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

void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	initialize_struct(t_main_parse *parse_struct)
{
	parse_struct->whole_file = NULL;
	parse_struct->c_red = 0;
	parse_struct->c_green = 0;
	parse_struct->c_blue = 0;
	parse_struct->f_red = 0;
	parse_struct->f_green = 0;
	parse_struct->f_blue = 0;
	parse_struct->character.x = -1;
	parse_struct->character.y = -1;
	parse_struct->map_size.x = 0;
	parse_struct->map_size.y = 0;
	parse_struct->map_size.y = 0;
	parse_struct->map_size.x = 0;
	parse_struct->entity_counts.EA_count = 0;
	parse_struct->entity_counts.WE_count = 0;
	parse_struct->entity_counts.SO_count = 0;
	parse_struct->entity_counts.NO_count = 0;
	parse_struct->entity_counts.F_count = 0;
	parse_struct->entity_counts.C_count = 0;
	parse_struct->no_texture_path = NULL;
	parse_struct->ea_texture_path = NULL;
	parse_struct->so_texture_path = NULL;
	parse_struct->we_texture_path = NULL;
	parse_struct->file_path = NULL;
	parse_struct->cpy_sq_map = NULL;
}

int file_name_checker(char *file_path, char *extension)
{
	int file_path_len;
	int i;

	i = 3;
	file_path_len = ft_strlen(file_path) - 1;
	if (file_path[file_path_len] == '\n')
		file_path_len--;
	while(i)
	{
		if (file_path[file_path_len] != extension[i])
		{
			ft_putstr_fd("File extension is not valid\n", 2);
			return (0);
		}
		file_path_len--;
		i--;
	}
	return (1);
}

int north_case(char *line, t_main_parse *parse)
{
	char **splitted_line;

	if (parse->entity_counts.NO_count++ > 0)
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

int south_case(char *line, t_main_parse *parse)
{
	char **splitted_line;

	if (parse->entity_counts.SO_count++ > 0)
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

int west_case(char *line, t_main_parse *parse)
{
	char **splitted_line;

	if (parse->entity_counts.WE_count++ > 0)
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

int east_case(char *line, t_main_parse *parse)
{
	char **splitted_line;

	if (parse->entity_counts.EA_count++ > 0)
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


int comma_checker(char *num_set)
{
	int i;
	int comma_count;

	i = 0;
	comma_count = 0;
	while (num_set[i])
	{
		if (num_set[i] == ',')
			comma_count++;
		++i;
	}
	if (comma_count != 2)
		return (0);
	return (1);
}

int	check_if_allocated(char **rgb)
{
	if (!rgb)
	{
		ft_putstr_fd("Allocation Error\n", 2);
		return (0);
	}
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_putstr_fd("There is something wrong \
		about floor\n", 2);
		free_double_pointer(rgb);
		return (0);
	}
	return (1);
}

void trim_each(char **rgb)
{
	char *temp;
	int	i;

	i = -1;
	while (++i < 3)
	{
		temp = ft_strdup(rgb[i]);
		free(rgb[i]);
		rgb[i] = ft_strtrim(temp, " ");
		free(temp);
	}
	
}

int is_all_digit(char **rgb)
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
					break;
				return (0);
			}
			x++;
		}
	}
	return (1);
}

int is_all_rgb_value(t_main_parse *p)
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

char *get_nums(char *line, char c) // F veya C yolla
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == c && line[i + 1] == 32)
			break;
		i++;
	}
	i += 2;
	while(line[i] == 32)
		i++;
	x = i;
	while (line[i] && line[i] != '\n')
		i++;
	return (ft_substr(line, x, i - x));
}


int floor_case(char *line, t_main_parse *parse)
{
	char **splitted_nums;
	char *num_set;

	if (parse->entity_counts.F_count++ > 0)
		return (0);
	num_set = get_nums(line, 'F');
	if (!comma_checker(num_set))
		return (free(num_set), 0);
	splitted_nums = ft_split(num_set, ',');
	if (!splitted_nums || !splitted_nums[0] ||!splitted_nums[1] || !splitted_nums[2])
	{
		ft_putstr_fd("Invalid Floor Case\n", 2);
		free(num_set);
		free_double_pointer(splitted_nums);
		return (0);
	}
	if (!check_if_allocated(splitted_nums) || !fill_rgb_values(parse, splitted_nums, 'f'))
	{
		free_double_pointer(splitted_nums);
		return (free(num_set), 0);
	}
	free_double_pointer(splitted_nums);
	free(num_set);
	return (1);
}

int ceiling_case(char *line, t_main_parse *parse)
{
	char **splitted_nums;
	char *num_set;

	if (parse->entity_counts.C_count++ > 0)
		return (0);
	num_set = get_nums(line, 'C');
	if (!comma_checker(num_set))
		return (free(num_set), 0);
	splitted_nums = ft_split(num_set, ',');
	if (!splitted_nums || !splitted_nums[0] ||!splitted_nums[1] || !splitted_nums[2])
	{
		ft_putstr_fd("Invalid Ceiling Case\n", 2);
		free(num_set);
		free_double_pointer(splitted_nums);
		return (0);
	}
	if (!check_if_allocated(splitted_nums) || !fill_rgb_values(parse, splitted_nums, 'c'))
	{
		free(num_set);
		free_double_pointer(splitted_nums);
		return (0);
	}
	free_double_pointer(splitted_nums);
	free(num_set);
	return (1);
}

int count_verifier(t_main_parse *parser)
{
	if (parser->entity_counts.C_count == 1 && parser->entity_counts.EA_count == 1 && parser->entity_counts.F_count == 1 && parser->entity_counts.NO_count == 1 && parser->entity_counts.SO_count == 1 && parser->entity_counts.WE_count == 1)
		return (1);
	return (0);
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

void free_textures(t_main_parse *parser)
{
	if (parser->entity_counts.WE_count > 0)
		free(parser->we_texture_path);
	if (parser->entity_counts.NO_count > 0)
		free(parser->no_texture_path);
	if (parser->entity_counts.SO_count > 0)
		free(parser->so_texture_path);
	if (parser->entity_counts.EA_count > 0)
		free(parser->ea_texture_path);
}

int entity_validator(t_intptr *ct)
{
	if (ct->EA_count == 1 && ct->WE_count == 1\
		&& ct->SO_count == 1 && ct->NO_count == 1
		&& ct->F_count == 1 && ct->C_count == 1)
			return (1);
	return (0);
}

int fill_textures(t_main_parse *parser)
{
	int	i;
	char *current_line;

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

void reset_entity_count(t_main_parse *parse)
{
	parse->entity_counts.EA_count = 0;
	parse->entity_counts.WE_count = 0;
	parse->entity_counts.NO_count = 0;
	parse->entity_counts.SO_count = 0;
	parse->entity_counts.F_count = 0;
	parse->entity_counts.C_count = 0;
}


void	counterr(char *line, t_main_parse *parse)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		parse->entity_counts.NO_count++;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		parse->entity_counts.SO_count++;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		parse->entity_counts.WE_count++;
	else if (line[0] == 'F' && line[1] == ' ')
		parse->entity_counts.F_count++;
	else if (line[0] == 'C' && line[1] == ' ')
		parse->entity_counts.C_count++;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		parse->entity_counts.EA_count++;
}

void pass_blank(t_main_parse* parse, char *trimmed, int *i)
{
	*i += 1;
	while (parse->whole_file[*i])
	{
		trimmed = ft_strtrim(parse->whole_file[*i], " ");
		if (trimmed[0] != '\n')
		{
			free(trimmed);
			return ;
		}
		free(trimmed);
		*i += 1;
	}
}

void pass_attributes(t_main_parse* parse, char *trimmed, int *i)
{
	while (parse->whole_file[*i])
	{
		trimmed = ft_strtrim(parse->whole_file[*i], " ");
		counterr(trimmed, parse);
		free(trimmed);
		if (entity_validator(&parse->entity_counts))
			break;
		*i += 1;
	}
}

void go_eof(t_main_parse *parse, int *i)
{
	while(parse->whole_file[*i])
		*i += 1;
}

void clean_newlines(char **map, int i)
{
	char *temp;

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
	int x;

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

int check_extra_horizontally(t_main_parse *parser)
{
	f_fill(parser, parser->character.y, parser->character.x);
	return (flf_check(parser->cpy_sq_map));
}

int check_extra_map_vertical(t_main_parse *parse, int i)
{
	char *temp;

	while (parse->map[i])
	{
		temp = ft_strtrim(parse->map[i++], " ");
		if (temp[0] == '\n')
		{
			free(temp);
			break;
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

int component_verifier(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
	{
		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			return (2);
		return (1);
	}
	return (0);
}

int invalid_component_check(t_main_parse *parse)
{
	int	i;
	int	j;
	int f;

	i = 0;
	while (parse->map[i])
	{
		j = 0;
		while(parse->map[i][j])
		{
			f = component_verifier(parse->map[i][j]);
			if (f == 0)
				return (0);
			else if (f == 2)
			{
				if (parse->character.x != -1 && parse->character.y != -1)
					return (0);
				parse->character.x = j;
				parse->character.y = i;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int get_max_x(char **map)
{
	int max_value;
	int y;
	int x;

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

int checker(char **map, int y, int x)
{
	char *str = ft_strdup("NSWE01");
	if (y == 0 || x == 0)
		return (free(str), 0);
	if (!ft_strchr(str, map[y][x - 1]))
		return (free(str), 0);
	if (!ft_strchr(str, map[y][x + 1]))
		return (free(str), 0);
	if (!map[y + 1])
		return (free(str), 0);
	if (!map[y - 1])
		return (free(str), 0);
	if (!ft_strchr(str, map[y + 1][x]))
		return (free(str), 0);
	if (!ft_strchr(str, map[y - 1][x]))
		return (free(str), 0);
	free(str);
	return (1);
}

int blank_checker(char **map)
{
	int y;
	int x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				if (!checker(map, y, x))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	start_parse(char *file_path, t_main_parse *parser_str)
{
	initialize_struct(parser_str);
	int fd;

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
	if (!fill_textures(parser_str))
	{
		free(parser_str->file_path);
		free_double_pointer(parser_str->whole_file);
		return (0);
	}
	if (!file_name_checker(parser_str->ea_texture_path, ".xpm") ||
		!file_name_checker(parser_str->we_texture_path, ".xpm") ||
		!file_name_checker(parser_str->so_texture_path, ".xpm") ||
		!file_name_checker(parser_str->no_texture_path, ".xpm"))
	{
		free(parser_str->file_path);
		free_double_pointer(parser_str->whole_file);
		free_textures(parser_str);
		return (0);
	}
	reset_entity_count(parser_str);
	fill_map(parser_str);
	if (!check_extra_map_vertical(parser_str, 0))
		return (0);
	clean_newlines(parser_str->map, 0);
	if (!invalid_component_check(parser_str))
		return (0);
	parser_str->cpy_sq_map = cpy_sq_map(parser_str->map, parser_str);
	if (!parser_str->cpy_sq_map)
		return (0);
	if (!check_extra_horizontally(parser_str))
		return (0);
	if (!blank_checker(parser_str->map))
		return (0);
	return (1);


	// ft_putendl_fd(parser_str.no_texture_path, 1);
	// ft_putendl_fd(parser_str.ea_texture_path, 1);
	// ft_putendl_fd(parser_str.we_texture_path, 1);
	// ft_putendl_fd(parser_str.so_texture_path, 1);
	// printf("F_red: %d\n", parser_str.f_red);
	// printf("F_green: %d\n", parser_str.f_green);
	// printf("F_blue: %d\n", parser_str.f_blue);
	// printf("C_red: %d\n", parser_str.c_red);
	// printf("C_green: %d\n", parser_str.c_green);
	// printf("C_blue: %d\n", parser_str.c_blue);
	return (1);
}

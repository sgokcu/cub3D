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

int	count_lines_of_file(int fd)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * 1);
	str[0] = 'a';
	while (str)
	{
		free (str);
		str = get_next_line(fd);
		i++;
	}
	return (i);
}

int	fill_whole_file(t_main_parse *parse_struct, int fd)
{
	int line_count;
	int i;

	i = -1;
	line_count = count_lines_of_file(fd);
	close(fd);
	fd = open(parse_struct->file_path, O_RDWR);
	if (fd == -1)
	{
		free(parse_struct->file_path);
		ft_putstr_fd("File not found\n", 2);
		return (0);
	}
	parse_struct->whole_file = malloc(sizeof(char *) * (line_count + 1));
	if (!parse_struct->whole_file)
	{
		ft_putstr_fd("There isn't enough space on the device\n", 2);
		free(parse_struct->file_path);
		return (0);
	}
	// printf("line count : %d\n", line_count);
	while (++i < line_count)
		parse_struct->whole_file[i] = get_next_line(fd); // geldi
	parse_struct->whole_file[i] = NULL;
	close(fd);
	return (1);
}

void fill_index(int i, t_main_parse *parser, char **sq_map)
{
	int y = 0;
	sq_map[i] = malloc(sizeof(char) * (parser->map_size.x + 3));
	while (y < parser->map_size.x + 2)
		sq_map[i][y++] = CHAR;
	sq_map[i][y] = '\0';
}

char **cpy_sq_map(char **map, t_main_parse *parser)
{
	int max_y;
	int i;
	int y;
	char **sq_map;

	max_y = 0;
	while (map[max_y])
		max_y++;
	if (max_y < 3)
		return (NULL);
	parser->map_size.x = get_max_x(map);
	sq_map = malloc(sizeof(char *) * (max_y + 3));
	fill_index(0, parser, sq_map);
	y = 1;
	while (map[y - 1])
	{
		i = 1;
		sq_map[y] = malloc(sizeof(char) * (parser->map_size.x + 3));
		sq_map[y][0] = CHAR;
		while (map[y - 1][i - 1])
		{
			sq_map[y][i] = map[y - 1][i - 1];
			i++;
		}
		while (i < (parser->map_size.x + 2))
		{
			sq_map[y][i] = CHAR;
			i++;
		}
		sq_map[y][i] = '\0';
		y++;
	}
	fill_index(y, parser, sq_map);
	sq_map[y + 1] = NULL;
	parser->map_size.y = y;
	return (sq_map);
}

int	fill_map(t_main_parse *parse)
{
	int i;
	int map_start;

	i = 0;
	pass_attributes(parse, NULL, &i);
	pass_blank(parse, NULL, &i);
	map_start = i;
	go_eof(parse, &i);
	parse->map = malloc(sizeof(char *) * (i - map_start + 1));
	i = 0;
	while (parse->whole_file[map_start])
	{
		parse->map[i] = ft_strdup(parse->whole_file[map_start]);
		map_start++;
		i++;
	}
	parse->map[i] = NULL;
	parse->map_size.y = i;
	return (1);
}

char **strdup_double(char **str)
{
	char **ret;
	int	i;

	i = 0;
	while (str[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

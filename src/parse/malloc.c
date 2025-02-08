/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:40:17 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/08 13:57:12 by sgokcu           ###   ########.fr       */
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
	int	line_count;
	int	i;

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
	while (++i < line_count)
		parse_struct->whole_file[i] = get_next_line(fd);
	parse_struct->whole_file[i] = NULL;
	close(fd);
	return (1);
}

void	fill_index(int i, t_main_parse *parser, char **sq_map)
{
	int	y;

	y = 0;
	sq_map[i] = malloc(sizeof(char) * (parser->map_size.x + 3));
	while (y < parser->map_size.x + 2)
		sq_map[i][y++] = CHAR;
	sq_map[i][y] = '\0';
}

char	**strdup_double(char **str)
{
	char	**ret;
	int		i;

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

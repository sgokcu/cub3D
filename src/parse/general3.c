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
	parse_struct->ch.p_loc.x = -1;
	parse_struct->ch.p_loc.y = -1;
	parse_struct->map_size.x = 0;
	parse_struct->map_size.y = 0;
	parse_struct->map_size.y = 0;
	parse_struct->map_size.x = 0;
	reset_entity_count(parse_struct);
	parse_struct->no_texture_path = NULL;
	parse_struct->ea_texture_path = NULL;
	parse_struct->so_texture_path = NULL;
	parse_struct->we_texture_path = NULL;
	parse_struct->file_path = NULL;
	parse_struct->cpy_sq_map = NULL;
	parse_struct->s_line = NULL;
}

int	file_name_checker(char *file_path, char *extension)
{
	int	file_path_len;
	int	i;

	i = 3;
	file_path_len = ft_strlen(file_path) - 1;
	if (file_path[file_path_len] == '\n')
		file_path_len--;
	while (i)
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

int	comma_checker(char *num_set)
{
	int	i;
	int	comma_count;

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

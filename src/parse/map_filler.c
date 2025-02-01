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

void go_eof(t_main_parse *parse, int *i)
{
	while(parse->whole_file[*i])
		*i += 1;
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
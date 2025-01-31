/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/29 19:20:14 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cub3d(char **av)
{
	t_main_parse parser;
	if (!start_parse(av[1], &parser))
	{
		ft_putstr_fd("Parse Error\n", 2);
		exit(0);
	}
	free(parser.file_path);
	free_double_pointer(parser.whole_file);
	free(parser.no_texture_path);
	free(parser.ea_texture_path);
	free(parser.we_texture_path);
	free(parser.so_texture_path);
	free_double_pointer(parser.map);
	free_double_pointer(parser.cpy_sq_map);
	return;
	return;


}

int main(int ac, char **av)
{
	if (ac == 2)
		cub3d(av);
	else
		ft_putstr_fd("Invalid argument count\n", 2);
}
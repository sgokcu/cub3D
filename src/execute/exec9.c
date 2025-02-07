/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:33 by erkoc             #+#    #+#             */
/*   Updated: 2025/02/07 15:29:37 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all(t_main_parse *parser)
{
	free(parser->file_path);
	free_double_pointer(parser->whole_file);
	free(parser->no_texture_path);
	free(parser->ea_texture_path);
	free(parser->we_texture_path);
	free(parser->so_texture_path);
	free_double_pointer(parser->map);
	free_double_pointer(parser->cpy_sq_map);
}

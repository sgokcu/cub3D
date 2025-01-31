/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:47:22 by erkoc             #+#    #+#             */
/*   Updated: 2023/12/19 17:08:06 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*str_new;
	size_t	x;

	x = 0;
	str = (char *)s1;
	str_new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!str_new)
		return (NULL);
	while (str[x])
	{
		str_new[x] = str[x];
		x++;
	}
	str_new[x] = 0;
	return (str_new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:41:32 by erkoc             #+#    #+#             */
/*   Updated: 2023/12/18 19:15:54 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;
	char	*hay;
	char	*ned;

	hay = (char *)haystack;
	ned = (char *)needle;
	i = 0;
	x = 0;
	if (!ned[x])
		return (hay);
	while (hay[i] && i < len)
	{
		x = 0;
		while ((hay[i + x] == ned[x]) && i + x < len)
		{
			x++;
			if (ned[x] == 0)
				return (hay + i);
		}
		i++;
	}
	return (NULL);
}

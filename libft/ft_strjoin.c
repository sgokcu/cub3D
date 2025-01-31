/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:49:15 by erkoc             #+#    #+#             */
/*   Updated: 2023/12/19 16:24:44 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ss1;
	char	*ss2;
	char	*allocated;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	ss1 = (char *)s1;
	ss2 = (char *)s2;
	allocated = malloc(sizeof(char) * (ft_strlen(ss1) + ft_strlen(ss2)) + 1);
	if (!allocated)
		return (NULL);
	while (ss1[i])
	{
		allocated[i] = ss1[i];
		i++;
	}
	while (ss2[y])
		allocated[i++] = ss2[y++];
	allocated[i] = 0;
	return (allocated);
}

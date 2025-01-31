/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:27 by erkoc             #+#    #+#             */
/*   Updated: 2023/12/19 16:41:24 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exists(int c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		x;
	int		len;
	size_t	ft;
	size_t	lt;

	x = 0;
	if ((!s1) || (!set))
		return (NULL);
	ft = 0;
	lt = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (ft_exists(s1[ft], set))
		ft++;
	while (lt > ft && ft_exists(s1[lt - 1], set))
		lt--;
	len = lt - ft;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s1[ft] && len-- > 0)
		str[x++] = s1[ft++];
	str[x] = 0;
	return (str);
}

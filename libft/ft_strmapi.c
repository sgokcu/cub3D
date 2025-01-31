/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erkoc <erkoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:08:40 by erkoc             #+#    #+#             */
/*   Updated: 2023/12/19 16:40:15 by erkoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;
	char	*ss;

	ss = (char *)s;
	i = 0;
	str = malloc(sizeof(char) * ft_strlen(ss) + 1);
	if (!str)
		return (NULL);
	while (ss[i])
	{
		str[i] = f(i, ss[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

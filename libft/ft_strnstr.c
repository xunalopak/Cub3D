/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:19:35 by rchampli          #+#    #+#             */
/*   Updated: 2021/10/27 20:19:35 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	dest = (char *)s1;
	if (!s2)
		return (dest);
	if (ft_strlen(s2) == 0 || s1 == s2)
		return (dest);
	while (dest[i] && i < len)
	{
		j = 0;
		if (dest[i] == s2[j])
		{
			while (dest[i + j] == s2[j] && dest && s2 && i + j < len)
			{
				if (s2[j + 1] == '\0' || j == ft_strlen(s2))
					return (dest + i);
				j++;
			}
		}
		i++;
	}
	return (0);
}

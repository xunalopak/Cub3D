/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:10:10 by rchampli          #+#    #+#             */
/*   Updated: 2021/10/27 19:10:10 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;
	size_t	j;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	j = d_len;
	if (size == 0)
		return (s_len);
	if (size < d_len)
		return (s_len + size);
	else
	{
		while (src[i] && (d_len + i) < size)
			dest[j++] = src[i++];
		if ((d_len + i) == size && d_len < size)
			dest[--j] = '\0';
		else
			dest[j] = '\0';
		if (d_len < size)
			return (d_len + s_len);
		return (d_len + s_len);
	}
}

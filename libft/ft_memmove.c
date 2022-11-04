/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:23:10 by rchampli          #+#    #+#             */
/*   Updated: 2021/10/11 16:23:10 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	unsigned int	i;

	i = 0;
	tmp1 = (unsigned char *)src;
	tmp2 = (unsigned char *)dest;
	while (i < n)
	{
		tmp2[n - 1] = tmp1[n - 1];
		n--;
	}
	return (dest);
}

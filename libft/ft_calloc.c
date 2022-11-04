/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:16:14 by rchampli          #+#    #+#             */
/*   Updated: 2021/11/01 16:16:14 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*new;
	unsigned int	total;

	total = size * nmemb;
	new = (char *)malloc(total);
	if (!new || total == 0)
		return (0);
	return (ft_memset(new, 0, total));
}

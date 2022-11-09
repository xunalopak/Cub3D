/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:10:54 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/09 00:33:20 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 07:09:02 by rchampli          #+#    #+#             */
/*   Updated: 2022/10/21 07:09:13 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_count(char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (*s == c)
			ret++;
		s++;
	}
	return (ret);
}

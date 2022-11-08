/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:58:44 by rchampli          #+#    #+#             */
/*   Updated: 2021/10/27 20:58:44 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 1;
	while ((str[j] >= 9 && str[j] <= 13) || (str[j] == ' '))
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			n = n * -1;
		j++;
	}
	while (str[j] >= 48 && str[j] <= 57)
	{
		i = i * 10 + (str[j] - 48);
		j++;
	}
	return (i * n);
}

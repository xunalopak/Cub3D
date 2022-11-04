/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:10:54 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/02 11:29:19 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

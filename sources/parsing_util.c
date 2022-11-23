/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:44:01 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/23 18:44:16 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse2(char **temp)
{
	char	*old_temp;
	int		x;

	x = 2;
	if (temp[x] != NULL)
	{
		while (temp[x])
		{
			old_temp = temp[1];
			temp[1] = ft_strjoin(temp[1], temp[x++]);
		}
	}
	(void)old_temp;
}

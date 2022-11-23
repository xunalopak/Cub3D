/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:18:02 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/23 19:04:31 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		left_str;
	int		buff;
	char	*str;

	if (s1 && s2)
	{
		left_str = ft_strlen(s1);
		buff = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (left_str + buff + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[left_str] = s2[i];
			left_str++;
		}
		str[left_str] = '\0';
		return (str);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:16:51 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/07 11:15:42 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_cnt(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			cnt++;
			while (*s != '\0' && *s != c)
			{
				s++;
			}
		}
	}
	return (cnt);
}

char	**free_machine(char **s, int idx)
{
	while (s[idx] != NULL && idx >= 0)
	{
		free(s[idx]);
		s[idx] = NULL;
		idx--;
	}
	free(s);
	s = NULL;
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	int		arr[3];
	char	**words;

	words = (char **)malloc(sizeof(char *) * (get_cnt(s, c) + 1));
	if (!s || !(words))
		return (NULL);
	arr[2] = get_cnt(s, c);
	arr[0] = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			arr[1] = 0;
			while (*(s + arr[1]) && *(s + arr[1]) != c)
				arr[1]++;
			words[arr[0]++] = ft_substr(s, 0, arr[1]);
			if (arr[0] < arr[2] && !words[arr[0] - 1])
				return (free_machine(words, arr[0]));
			s += arr[1];
		}
	}
	words[arr[0]] = 0;
	return (words);
}

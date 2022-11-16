/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:41 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:01:09 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_next_line(int fd, char **line, t_data *data)
{
	int		i;
	int		n;
	char	c;
	char	*str;

	i = 0;
	if (fd < 0)
		return (-1);
	str = (char *)malloc(1000 + 1);
	if (!str)
		return (-1);
	n = read(fd, &c, 1);
	while (n && c != '\n' && c != '\0')
	{
		str[i++] = c;
		n = read(fd, &c, 1);
	}
	str[i] = '\0';
	*line = str;
	if (ft_strlen(*line) != 0 && n == 0)
		data->map.gnl = 1;
	return (n);
}

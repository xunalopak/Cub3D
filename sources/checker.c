/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:01:42 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:00:45 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check1(char *line)
{
	if (!line)
		ft_error("Invalid map");
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '\0')
			ft_error("Invalid map");
		line++;
	}
}

void	check2(char c)
{
	if (c != ' ' && c != '1' && c != '0' && c != 'N' && c != 'W'
		&& c != 'E' && c != 'S')
		ft_error("Invalid map");
}

void	check3(int i, int j, t_data *data)
{
	if (i - 1 >= 0 && i - 1 < data->map.height)
		if (data->map.map[i - 1][j] != ' ' && data->map.map[i - 1][j] != '1'
			&& data->map.map[i - 1][j] != '\0')
			ft_error("Invalid map");
	if (i + 1 >= 0 && i + 1 < data->map.height)
		if (data->map.map[i + 1][j] != ' ' && data->map.map[i + 1][j] != '1'
			&& data->map.map[i + 1][j] != '\0')
			ft_error("Invalid map");
	if (j - 1 >= 0 && j - 1 < data->map.width)
		if (data->map.map[i][j - 1] != ' ' && data->map.map[i][j - 1] != '1'
			&& data->map.map[i + 1][j] != '\0')
			ft_error("Invalid map");
	if (j + 1 >= 0 && j + 1 < data->map.width)
		if (data->map.map[i][j + 1] != ' ' && data->map.map[i][j + 1] != '1'
			&& data->map.map[i + 1][j] != '\0')
			ft_error("Invalid map");
}

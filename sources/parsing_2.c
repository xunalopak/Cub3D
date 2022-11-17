/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:34 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/14 15:09:02 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_color(char **temp, t_data *data)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	if (get_count(temp[1], ',') != 2)
	{
		free_matrix(temp);
		cub3D_error("Bad color settings", data);
	}
	rgb = ft_split(temp[1], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		cub3D_error("Bad color settings", data);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		cub3D_error("Bad color settings", data);
	color = ((r << 16) + (g << 8) + b);
	free_matrix(rgb);
	return (color);
}

void	ft_map(t_data *data)
{
	int	i;

	i = 0;
	data->map.map = malloc((data->map.height + 1) * sizeof(char *));
	if (!data->map.map)
		cub3D_error("Malloc failed", data);
	while (i < data->map.height)
	{
		data->map.map[i] = malloc((data->map.width + 1) * sizeof(char *));
		if (!data->map.map[i])
			cub3D_error("Malloc failed", data);
		i++;
	}
	data->map.map[i] = 0;
}

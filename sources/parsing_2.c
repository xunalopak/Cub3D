/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:34 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:00:45 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dir(t_data *data)
{
	if (data->player.dir_symbol == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.71;
	}
	else if (data->player.dir_symbol == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.71;
	}
	else if (data->player.dir_symbol == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.71;
	}
	else if (data->player.dir_symbol == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.71;
	}
}

int	ft_parse_color(char **temp)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	if (get_count(temp[1], ',') != 2)
	{
		free_matrix(temp);
		ft_error("Bad color settings");
	}
	rgb = ft_split(temp[1], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_error("Bad color settings");
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		ft_error("Bad color settings");
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
		ft_error("Malloc failed");
	while (i < data->map.height)
	{
		data->map.map[i] = malloc((data->map.width + 1) * sizeof(char *));
		if (!data->map.map[i])
			ft_error("Malloc failed");
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:34 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/09 16:10:36 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_map(void)
{
	int	i;

	i = 0;
	map.map = malloc((map.height + 1) * sizeof(char *));
	if (!map.map)
		ft_error("Malloc failed");
	while (i < map.height)
	{
		map.map[i] = malloc((map.width + 1) * sizeof(char *));
		if (!map.map[i])
			ft_error("Malloc failed");
		i++;
	}
}

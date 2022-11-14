/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:36 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/14 15:05:36 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size_process(char *line, int *n, t_data *data)
{
	if (map.flag)
		ft_error("Invalid map");
	if (*n < 6)
		(*n)++;
	else
	{
		if (ft_strlen(line) > map.width)
			data->map.width = ft_strlen(line);
		data->map.height++;
		(*n)++;
	}
}

void	map_size(char *file, t_data *data)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_is_empty(line))
			map_size_process(line, &n, data);
		else if (n > 6)
			data->map.flag = 1;
		free(line);
	}
	if (data->map.gnl)
		data->map.height++;
	free(line);
	close(fd);
}

void	parse_m2(int i, int j, t_data *data)
{
	check2(data->map.map[i][j]);
	if (j == 0 || j == data->map.width - 1)
		if (data->map.map[i][j] != ' ' && data->map.map[i][j] != '1')
			ft_error("Invalid map");
	if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'W'
		|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'S')
	{
		data->player.count++;
		if (data->player.count == 1)
		{
			data->player.x = j;
			data->player.y = i;
			data->player.dir_symbol = data->map.map[i][j];
		}
		data->map.map[i][j] = '0';
	}
	if (data->map.map[i][j] == ' ')
		check3(i, j);
}

int	parse_m(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		if (i == 0 || i == data->map.height - 1)
			check1(data->map.map[i]);
		j = 0;
		while (data->map.map[i][j])
		{
			parse_m2(i, j, data);
			j++;
		}
		i++;
	}
	if (data->player.count == 0)
		ft_error("No player");
	return (0);
}

void	parse_map(char *line, int fd, t_data *data)
{
	if (close(fd) == -1)
		ft_error("Close error");
	if (data->map.count != 6)
		ft_error("Verify .cub file");
	if (parse_m(data))
		ft_error("Invalid map");
	free(line);
}

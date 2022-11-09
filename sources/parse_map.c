/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:36 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/09 16:12:55 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_size_process(char *line, int *n)
{
	if (map.flag)
		ft_error("Invalid map");
	if (*n < 6)
		(*n)++;
	else
	{
		if (ft_strlen(line) > map.width)
			map.width = ft_strlen(line);
		map.height++;
		(*n)++;
	}
}

void	map_size(char *file)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_is_empty(line))
			map_size_process(line, &n);
		else if (n > 6)
			map.flag = 1;
		free(line);
	}
	if (map.gnl)
		map.height++;
	free(line);
	close(fd);
}

void	parse_m2(int i, int j)
{
	check2(map.map[i][j]);
	if (j == 0 || j == map.width - 1)
		if (map.map[i][j] != ' ' && map.map[i][j] != '1')
			ft_error("Invalid map");
	if (map.map[i][j] == 'N' || map.map[i][j] == 'W'
		|| map.map[i][j] == 'E' || map.map[i][j] == 'S')
	{
		player.count++;
		if (player.count == 1)
		{
			player.x = j;
			player.y = i;
			player.dir_symbol = map.map[i][j];
		}
		map.map[i][j] = '0';
	}
	if (map.map[i][j] == ' ')
		check3(i, j);
}

int	parse_m(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		if (i == 0 || i == map.height - 1)
			check1(map.map[i]);
		j = 0;
		while (map.map[i][j])
		{
			parse_m2(i, j);
			j++;
		}
		i++;
	}
	if (player.count == 0)
		ft_error("No player");
	return (0);
}

void	parse_map(char *line, int fd)
{
	if (close(fd) == -1)
		ft_error("Close error");
	if (map.count != 6)
		ft_error("Verify .cub file");
	if (parse_m())
		ft_error("Invalid map");
	free(line);
}

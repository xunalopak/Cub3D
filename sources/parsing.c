/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:32 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/09 16:12:00 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture2(char **temp)
{
	if (temp[0][0] == 'N' && temp[0][1] == 'O' && temp[0][2] == '\0')
		map.fd_no = ft_strdup(temp[1]);
	else if (temp[0][0] == 'S' && temp[0][1] == 'O' && temp[0][2] == '\0')
		map.fd_so = ft_strdup(temp[1]);
	else if (temp[0][0] == 'W' && temp[0][1] == 'E' && temp[0][2] == '\0')
		map.fd_we = ft_strdup(temp[1]);
	else if (temp[0][0] == 'E' && temp[0][1] == 'A' && temp[0][2] == '\0')
		map.fd_ea = ft_strdup(temp[1]);
	else if (temp[0][0] == 'F' && temp[0][1] == '\0')
	{
		if (map.f >= 1)
			ft_error("Duplicate F");
		map.floor = ft_parse_color(temp);
		map.f++;
	}
	else if (temp[0][0] == 'C' && temp[0][1] == '\0')
	{
		if (map.c == 1)
			ft_error("Duplicate C");
		map.ceiling = ft_parse_color(temp);
		map.c++;
	}
	else
		return (1);
	return (0);
}

int	parse_texture(char **temp)
{
	if (parse_texture2(temp))
		return (1);
	free_matrix(temp);
	map.count = 6;
	return (0);
}

void	fill_map(char *line, int n)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
		map.map[n][i] = line[i];
	while (i < map.width)
	{
		map.map[n][i] = ' ';
		i++;
	}
	map.map[n][i] = '\0';
}

void	ft_parse(char *line, int n)
{
	char	**temp;

	if (n >= 0 && n <= 5)
	{
		temp = ft_split(line, ' ');
		if (temp[2] != NULL)
		{
			free_matrix(temp);
			ft_error("Invalid line of texture?");
		}
		if (parse_texture(temp))
		{
			free_matrix(temp);
			ft_error("Invalid line of texture!");
		}
		return ;
	}
	else if (n > 5)
		fill_map(line, n - 6);
	else
		ft_error("Invalid line in .cub!");
}

void	parse(char *file)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line))
	{
		if (!ft_is_empty(line))
		{
			if (n == 5)
			{
				map_size(file);
				ft_map();
			}
			ft_parse(line, n);
			n++;
		}
		if (line)
			free(line);
	}
	parse_map(line, fd);
}

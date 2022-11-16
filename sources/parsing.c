/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:32 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:02:27 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture2(char **temp, t_data *data)
{
	if (temp[0][0] == 'N' && temp[0][1] == 'O' && temp[0][2] == '\0')
		data->map.fd_no = ft_strdup(temp[1]);
	else if (temp[0][0] == 'S' && temp[0][1] == 'O' && temp[0][2] == '\0')
		data->map.fd_so = ft_strdup(temp[1]);
	else if (temp[0][0] == 'W' && temp[0][1] == 'E' && temp[0][2] == '\0')
		data->map.fd_we = ft_strdup(temp[1]);
	else if (temp[0][0] == 'E' && temp[0][1] == 'A' && temp[0][2] == '\0')
		data->map.fd_ea = ft_strdup(temp[1]);
	else if (temp[0][0] == 'F' && temp[0][1] == '\0')
	{
		if (data->map.f >= 1)
			ft_error("Duplicate F");
		data->map.floor = ft_parse_color(temp);
		data->map.f++;
	}
	else if (temp[0][0] == 'C' && temp[0][1] == '\0')
	{
		if (data->map.c == 1)
			ft_error("Duplicate C");
		data->map.ceiling = ft_parse_color(temp);
		data->map.c++;
	}
	else
		return (1);
	return (0);
}

int	parse_texture(char **temp, t_data *data)
{
	if (parse_texture2(temp, data))
		return (1);
	free_matrix(temp);
	data->map.count = 6;
	return (0);
}

void	fill_map(char *line, int n, t_data *data)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
		data->map.map[n][i] = line[i];
	while (i < data->map.width)
	{
		data->map.map[n][i] = ' ';
		i++;
	}
	data->map.map[n][i] = '\0';
}

void	ft_parse(char *line, int n, t_data *data)
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
		if (parse_texture(temp, data))
		{
			free_matrix(temp);
			ft_error("Invalid line of texture!");
		}
		return ;
	}
	else if (n > 5)
		fill_map(line, n - 6, data);
	else
		ft_error("Invalid line in .cub!");
}

void	parse(char *file, t_data *data)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line, data))
	{
		if (!ft_is_empty(line))
		{
			if (n == 5)
			{
				map_size(file, data);
				ft_map(data);
			}
			ft_parse(line, n, data);
			n++;
		}
		if (line)
			free(line);
	}
	parse_map(line, fd, data);
}

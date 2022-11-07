/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/07 12:08:19 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_map(void)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		free(map.map[i++]);
	}
	free(map.map);
}

void	cleanup(void)
{
	// if (win.west.img)
	// 	mlx_destroy_image(win.mlx, win.west.img);
	// if (win.east.img)
	// 	mlx_destroy_image(win.mlx, win.east.img);
	// if (win.north.img)
	// 	mlx_destroy_image(win.mlx, win.north.img);
	// if (win.south.img)
	// 	mlx_destroy_image(win.mlx, win.south.img);
	// if (win.data.img)
	// 	mlx_destroy_image(win.mlx, win.data.img);
	// if (win.win)
	// 	mlx_destroy_window(win.mlx, win.win);
	if (map.fd_ea)
		free(map.fd_ea);
	if (map.fd_no)
		free(map.fd_no);
	if (map.fd_so)
		free(map.fd_so);
	if (map.fd_we)
		free(map.fd_we);
	if (map.map)
		destroy_map();
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
		if (map.f == 1)
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
	map.n++;
	free_matrix(temp);
	return (0);
}

void	fill_map(char *line, int n)
{
	int	i;

	i = 0;
	while (line[i])
		{
			map.map[n][i] = line[i];
			i++;
		}
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

	if (n <= 5)
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
	}
	else if (n > 5)
		fill_map(line, n - 6);
	else
		ft_error("Invalid line in .cub!");
}

void	map_size_process(char *line, int *n)
{
	if (map.flag)
		ft_error("Invalid map");
	if (*n < 6)
		(*n)++;
	else if (ft_strlen(line) > map.width)
	{
		map.width = ft_strlen(line);
		map.height++;
		(*n)++;
	}
	printf("Map height: %d, Map width : %d\n", map.height, map.width);
}

void	map_size(char *file)
{
	int	fd;
	int	n;
	char	*line;
	
	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_is_empty(line))
		{
			map_size_process(line, &n);
		}
		else if (n > 6)
			map.flag = 1;
		free(line);
	}
	if (map.gnl)
		map.height++;
	free(line);
	close(fd);
}

void	ft_map(void)
{
	int	i;

	i = 0;
	map.map = (char **)malloc(sizeof(char *) * (map.height + 1));
	if (!map.map)
		ft_error("Malloc failed");
	while (i < map.height)
	{
		map.map[i] = (char *)malloc(sizeof(char) * (map.width + 1));
		if (!map.map[i])
			ft_error("Malloc failed");
		i++;
	}
}

void	parse(char *file)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = ft_open(file);
	while (get_next_line(fd, &line) > 0)
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
			printf("no: %s so: %s we: %s ea: %s f: %i c: %i \n", map.fd_no, map.fd_so, map.fd_we, map.fd_ea, map.floor, map.ceiling);
		}
		if (line)
			free(line);
	}
	close(fd);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_error("Wrong number of arguments");
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_error("Wrong file extension");
	}
	parse(av[1]);
	cleanup();
}

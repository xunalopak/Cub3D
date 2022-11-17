/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/14 15:10:01 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

void	cleanup(t_data *data)
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
	if (data->map.fd_ea)
		free(data->map.fd_ea);
	if (data->map.fd_no)
		free(data->map.fd_no);
	if (data->map.fd_so)
		free(data->map.fd_so);
	if (data->map.fd_we)
		free(data->map.fd_we);
	if (data->map.map)
		destroy_map(&(data->map));
}

void	cub3D_error(char *str, t_data *data)
{
	dprintf(2, "%s\n", str);
	cleanup(data);
	ft_error(str);
}

void	init_map(t_map *map)
{
	map->map = 0;
	map->fd_no = 0;
	map->fd_so = 0;
	map->fd_we = 0;
	map->fd_ea = 0;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->height = 0;
	map->width = 0;
	map->max_width = 0;
	map->count = 0;
	map->ceiling = 0;
	map->floor = 0;
	map->gnl = 0;
	map->f = 0;
	map->c = 0;
	map->n = 0;
	map->flag = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_error("Wrong number of arguments");
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_error("Wrong file extension");
	}
	init_map(&(data.map));
	data.player.count = 0;
	parse(av[1], &data);
	data_mlx_init(&(data.mlx));
	render(&data);
	mlx_loop(data.mlx.mlx_ptr);
	printf("R: %d %d\n", data.map.width, data.map.height);
	cleanup(&data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/21 19:34:17 by rchampli         ###   ########.fr       */
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

void	ft_exit(int exit_code, t_data *data)
{
	printf("BYE\n");
	cleanup(data);
	exit(exit_code);
}

void	cleanup(t_data *data)
{
	if (data->mlx.west.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.west.img);
	if (data->mlx.east.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.east.img);
	if (data->mlx.north.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.north.img);
	if (data->mlx.south.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.south.img);
	if (data->mlx.img.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
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
	exit(0);
}

void	cub3d_error(char *str, t_data *data)
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

void	game(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win_ptr, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win_ptr, DESTROY_NOTIFY, 0, destroy_hook, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	//data.win.width = WIDTH;
	//data.win.height = HEIGHT;
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
	load_texture(&data);
	render(&data);
	game(&data);
	mlx_loop(data.mlx.mlx_ptr);
	cleanup(&data);
}

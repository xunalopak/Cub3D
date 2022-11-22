/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/21 21:42:06 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
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

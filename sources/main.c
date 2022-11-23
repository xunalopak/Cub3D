/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/23 16:35:13 by rchampli         ###   ########.fr       */
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

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (data->player.mouse_x < x)
		data->player.turn = ROTATE_LEFT;
	else if (data->player.mouse_x > x)
		data->player.turn = ROTATE_RIGHT;
	else
		data->player.turn = 0;
	data->player.mouse_x = x;
	return (0);
}

void	game(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win_ptr, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win_ptr, MOUSE_MOVE, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx.win_ptr, DESTROY_NOTIFY, 0, destroy_hook, data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
}

static void	draw_minimap(t_data *data)
{
	int	x;
	int	color;
	int	*img;
	int	i;

	data->mlx.minimap.img = mlx_new_image(data->mlx.mlx_ptr,
			MAP_LV * data->map.width, MAP_LV * data->map.height);
	data->mlx.minimap.addr = mlx_get_data_addr(data->mlx.minimap.img,
			&(data->mlx.minimap.bpp), &(data->mlx.minimap.length),
			&(data->mlx.minimap.endian));
	img = (int *)data->mlx.minimap.addr;
	x = -1;
	while (++x < data->map.width * data->map.height)
	{
		if (data->map.map[x / data->map.width][x % data->map.width] == '0')
			color = 0xffffff;
		else
			color = 0;
		i = -1;
		while (++i < MAP_LV * MAP_LV)
			img[(MAP_LV * (x % data->map.width) + i % MAP_LV)
				+ (MAP_LV * (x / data->map.width) + i / MAP_LV)
				* MAP_LV * data->map.width] = color;
	}
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
	draw_minimap(&data);
	load_texture(&data);
	render(&data);
	game(&data);
	mlx_loop(data.mlx.mlx_ptr);
	cleanup(&data);
}

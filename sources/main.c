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

void	destroy_map(void)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		free(map.map[i]);
		i++;
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
	parse(av[1], &data);
	printf("R: %d %d\n", data.map.width, data.map.height);
	cleanup();
}

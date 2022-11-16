/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/15 18:46:29 by rchampli         ###   ########.fr       */
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

void	texture_load(char *path, t_img *dest, t_data *data)
{
	int width;
	int height;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCouldn't open texture file");
	close(fd);
	dest->img = mlx_open_xpm_file(data->win.mlx, path, &width, &height);
	dest->addr = mlx_get_data_addr(dest->img, &dest->bpp, &dest->length, &dest->endian);
}

void	load_texture(t_data *data)
{
	texture_load(data->map.fd_no, &data->win.north, data);
	texture_load(data->map.fd_so, &data->win.south, data);
	texture_load(data->map.fd_we, &data->win.west, data);
	texture_load(data->map.fd_ea, &data->win.east, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.win.width = WIDTH;
	data.win.height = HEIGHT;
	ft_bzero(&data, sizeof(t_data));
	if (ac != 2)
	{
		ft_error("Wrong number of arguments");
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_error("Wrong file extension");
	}
	parse(av[1], &data);
	data.win.mlx = mlx_init();
	data.win.win = mlx_new_window(data.win.mlx, data.win.height, data.win.width, "Cub3D");
	data.win.img.img = mlx_new_image(data.win.mlx, data.win.height, data.win.width);
	data.win.img.addr = mlx_get_data_addr(data.win.img.img, &data.win.img.bpp,
			&data.win.img.length, &data.win.img.endian);
	load_textures(&data);
	cleanup();
}

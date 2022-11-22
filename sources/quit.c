/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:35:12 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/21 21:42:06 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

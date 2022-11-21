/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:23:14 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/21 19:17:30 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_load(char *path, t_img *dest, t_data *data)
{
	int	width;
	int	height;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Invalid texture path");
	close(fd);
	dest->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			path, &width, &height);
	dest->addr = mlx_get_data_addr(dest->img, &dest->bpp, &dest->length,
			&dest->endian);
}

u_int32_t	take_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->length + x * (img->bpp / 8));
	return (*(u_int32_t *)dst);
}

void	texture_load_array(t_img *src, u_int32_t dest[64][64])
{
	int	x;
	int	y;

	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			dest[x][y] = take_pixel(src, x, y);
			x++;
		}
		y++;
	}
}

void	load_texture(t_data *data)
{
	texture_load(data->map.fd_no, &data->mlx.north, data);
	texture_load(data->map.fd_so, &data->mlx.south, data);
	texture_load(data->map.fd_we, &data->mlx.west, data);
	texture_load(data->map.fd_ea, &data->mlx.east, data);
	texture_load_array(&data->mlx.north, data->mlx.north_array);
	texture_load_array(&data->mlx.south, data->mlx.south_array);
	texture_load_array(&data->mlx.west, data->mlx.west_array);
	texture_load_array(&data->mlx.east, data->mlx.east_array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/17 00:15:14 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color_from_texture(t_data *data, int face, double x, double y)
{
	int const	ix = (int)floor(x * 64.);
	int const	iy = (int)floor((1 - y) * 64.);

	if (face == 1)
		return (data->mlx.north_array[ix][iy]);
	else if (face == 2)
		return (data->mlx.east_array[ix][iy]);
	else if (face == 3)
		return (data->mlx.south_array[ix][iy]);
	else
		return (data->mlx.west_array[ix][iy]);
}

static void	draw_column(t_data *data, int x, t_inter hit)
{
	int				i;
	int				color;
	double			height;
	int *const		img = (int *)data->mlx.img.addr;

	color = 0;
	i = -1;
	while (++i < data->mlx.win_y)
	{
		height = data->player.height + hit.dst * data->mlx.y_ray[i];
		if (height < 0.)
			color = data->map.floor;
		else if (height > 1.)
			color = data->map.ceiling;
		else
			color = get_color_from_texture(data, hit.face, hit.pos, height);
	img[i * data->mlx.win_x + x] = color;
	}
}

void	render(t_data *data)
{
	int				i;
	double const	cosa = cos(data->player.rot);
	double const	sina = sin(data->player.rot);
	t_inter			hit;
	t_vec			ray;

	ray.x = data->mlx.z;
	i = -1;
	while (++i < data->mlx.win_x)
	{
		ray.y = data->mlx.x_ray[i];
		hit = calc_dst(data, vec_rot(&ray, cosa, sina));
		draw_column(data, i, hit);
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.minimap.img, 0, 0);
}

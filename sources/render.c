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
	int const	X = (int)floor(x * 64.);
	int const	Y = (int)floor((1 - y) * 64.);

	if (face == 0)
		return (data->mlx.south_array[X][Y]);
	else if (face == 1)
		return (data->mlx.west_array[X][Y]);
	else if (face == 2)
		return (data->mlx.north_array[X][Y]);
	else
		return (data->mlx.east_array[X][Y]);
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
			color = get_color_from_texture(data, hit.face, hit.pos1, height);
	img[i * data->mlx.win_x + x] = color;
	}
}

static t_inter	calc_dst(t_data	*data, t_vec dir)
{
	t_inter	ret;
	int		X;
	int		Y;
	int		dX;
	int		dY;
	double	dx;
	double	dy;

	X = (int)floor(data->player.pos.x);
	Y = (int)floor(data->player.pos.y);
	dX = 1;
	dY = 1;
	ret.dst = 0.;
	ret.face = 0;
	ret.pos1 = 0.;
	ret.pos2.x = data->player.pos.x - (double)X;
	ret.pos2.y = data->player.pos.y - (double)Y;
	ret.type = data->map.map[Y][X];

	if (dir.x < 0.)
	{
		dX = -1;
		ret.pos2.x = 1. - ret.pos2.x;
		dir.x = -dir.x;
	}
	if (dir.y < 0.)
	{
		dY = -1;
		ret.pos2.y = 1. - ret.pos2.y;
		dir.y = -dir.y;
	}
	while (ret.type == '0')
	{
		dx = (1. - ret.pos2.x) / dir.x;
		dy = (1. - ret.pos2.y) / dir.y;
		if (dx < dy)
		{
			ret.pos2.x = 0.;
			ret.pos2.y += dx * dir.y;
			ret.pos1 = ret.pos2.y;
			if (dY < 0)
				ret.pos1 = 1 - ret.pos1;
			ret.dst += dx;
			X += dX;
			ret.face = 1 - dX;
		}
		else
		{
			ret.pos2.x += dy * dir.x;
			ret.pos2.y = 0.;
			ret.pos1 = ret.pos2.x;
			if (dX < 0)
				ret.pos1 = 1 - ret.pos1;
			ret.dst += dy;
			Y += dY;
			ret.face = 2 - dY;
		}
		ret.type = data->map.map[Y][X];
	}
	return (ret);
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
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img, 0, 0);
}

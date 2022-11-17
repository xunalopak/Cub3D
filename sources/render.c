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

static void	draw_column(t_data *data, int x, t_inter hit)
{
	int				i;
	int				color;
	double			height;
	int *const		img = (int *)data->mlx.img.addr;

	color = 0;
	i = -1;
//dprintf(2, "%f\n", hit.dst);
	while (++i < data->mlx.win_y)
	{
		height = data->player.height + hit.dst * data->mlx.y_ray[i];
//dprintf(2, "%f %f %f %f\n", data->player.height, hit.dst, data->mlx.y_ray[i], height);
		if (height < 0.)
			color = data->map.floor;
		else if (height > 1.)
			color = data->map.ceiling;
		else
			color = 0X0000FF;
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

	X = (int)floor(data->player.x);
	Y = (int)floor(data->player.y);
	dX = 1;
	dY = 1;
	ret.dst = 0.;
	ret.face = 0;
	ret.pos1 = 0.;
	ret.pos2.x = data->player.x - (double)X;
	ret.pos2.y = data->player.y - (double)Y;
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
//dprintf(2, "xy %f %f\n", data->player.x, data->player.y);
//dprintf(2, "XY %d %d #%c#\n", X, Y, ret.type);
//dprintf(2, "dxy %f %f\n", dir.x, dir.y);
	while (ret.type == '0')
	{
		dx = (1. - ret.pos2.x) / dir.x;
		dy = (1. - ret.pos2.y) / dir.y;
		if (dx < dy)
		{
			ret.pos2.x = 0.;
			ret.pos2.y += dx * dir.y;
			ret.dst += dx;
			X += dX;
			ret.face = 1 - dX;
		}
		else
		{
			ret.pos2.x += dy * dir.x;
			ret.pos2.y = 0.;
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

i = -1;
while (data->map.map[++i])
dprintf(2, "%s\n", data->map.map[i]);
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

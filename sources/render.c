/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/14 15:22:24 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_column(t_data *data, int x, double dst, int dir)
{
	int			i;
	int			color;
	double		heigth;
	int *const	img = (int *)data->mlx.img;

	(void) dir;
	color = 0;
	i = -1;
	while (++i < data->mlx.win_y)
	{
		heigth = data->player.heigth + dst * data->mlx.y_ray[i];
		if (heigth < 0.)
			color = 0X0000FF;
		else if (heigth > 1.)
			color = 0XFF0000;
		else
			color = 0X00FF00;
	}
	img[i * data->mlx.win_x + x] = color;
}

static double	calc_dst(t_map *map, t_vec dir)
{
	return (5.);
}

void	render(t_data *data)
{
	int				i;
	double const	cosa = cos(data->player.rot);
	double const	sina = sin(data->player.rot);
	double			dst;
	int				dir;

	dst = calc_dst(&(data->map),
			vec_rot(&(data->mlx.x_ray[i]), cosa, sina), &dir);
	i = -1;
	while (++i < data->mlx.win_x)
		draw_column(data, i, dst, dir);
}

/*

float	fov = 100;
int		win_x = 1000;
float	rot = 0;
float	height = ?

f(x)
	fx = 2x/win_x - 1
	v = norm(fx, 1/tan(fov/2))
	v2 = (sinrot vx + cosrot vy, -cosrot vx + sinrot vy)

f(y,d)
	fy = (2y - win_y)/win_x * tan(fov/2)
	fy * d + height

*/

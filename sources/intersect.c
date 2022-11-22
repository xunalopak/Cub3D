/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/17 00:15:14 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_tmp(t_data *data, t_inter *ret, t_inter_data *tmp, t_vec *dir)
{
	tmp->ix = (int)floor(data->player.pos.x);
	tmp->iy = (int)floor(data->player.pos.y);
	tmp->d_ix = 1;
	tmp->d_iy = 1;
	tmp->pos.x = data->player.pos.x - (double)tmp->ix;
	tmp->pos.y = data->player.pos.y - (double)tmp->iy;
	tmp->axe = 0;
	ret->dst = 0.;
	ret->face = 0;
	ret->pos = 0.;
	ret->type = data->map.map[tmp->iy][tmp->ix];
	if (dir->x < 0.)
	{
		tmp->d_ix = -1;
		tmp->pos.x = 1. - tmp->pos.x;
		dir->x = -dir->x;
	}
	if (dir->y < 0.)
	{
		tmp->d_iy = -1;
		tmp->pos.y = 1. - tmp->pos.y;
		dir->y = -dir->y;
	}
}

static void	get_res(t_inter *ret, t_inter_data *tmp)
{
	if (tmp->axe)
	{
		ret->pos = 1 - tmp->pos.x;
		ret->face = 2 - tmp->d_iy;
	}
	else
	{
		ret->pos = tmp->pos.y;
		ret->face = 1 - tmp->d_ix;
	}
	if (tmp->d_ix * tmp->d_iy < 0)
		ret->pos = 1 - ret->pos;
}

static double	why(t_inter_data *tmp, double x, double y, double ret)
{
	tmp->pos.x = x;
	tmp->pos.y = y;
	return (ret);
}

t_inter	calc_dst(t_data	*data, t_vec dir)
{
	t_inter			ret;
	t_inter_data	tmp;

	init_tmp(data, &ret, &tmp, &dir);
	while (ret.type == '0')
	{
		tmp.d_x = (1. - tmp.pos.x) / dir.x;
		tmp.d_y = (1. - tmp.pos.y) / dir.y;
		if (tmp.d_x < tmp.d_y)
		{
			ret.dst += why(&tmp, 0., tmp.pos.y + tmp.d_x * dir.y, tmp.d_x);
			tmp.ix += tmp.d_ix;
			tmp.axe = 0;
		}
		else
		{
			ret.dst += why(&tmp, tmp.pos.x + tmp.d_y * dir.x, 0., tmp.d_y);
			tmp.iy += tmp.d_iy;
			tmp.axe = 1;
		}
		ret.type = data->map.map[tmp.iy][tmp.ix];
	}
	get_res(&ret, &tmp);
	return (ret);
}

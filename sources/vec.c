/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:44:42 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/14 14:16:09 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vec_norm(t_vec *vec)
{
	double const	inv_len = 1. / sqrt(vec->x * vec->x + vec->y * vec->y);

	vec->x *= inv_len;
	vec->y *= inv_len;
}

t_vec	vec_rot(t_vec const *vec, double cosa, double sina)
{
	t_vec	ret;

	ret.x = vec->x * cosa - vec->y * sina;
	ret.y = vec->x * sina + vec->y * cosa;
	return (ret);
}

void	vec_add(t_vec *vec1, t_vec vec2)
{
	vec1->x += vec2.x;
	vec1->y += vec2.y;
}

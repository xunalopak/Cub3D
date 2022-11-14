/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_mlx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:06:22 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/14 14:16:48 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_ray(t_mlx *mlx)
{
	int			i;
	float const	t = tan(mlx->fov / 2.);
	float const	inv_t = 1. / t;
	float const	inv_x = 1. / (float)mlx->win_x;

	i = -1;
	while (++i < mlx->win_x)
	{
		mlx->x_ray[i].x = 2. * (float)i * inv_x - 1.;
		mlx->x_ray[i].y = inv_t;
		vec_norm(mlx->x_ray + i);
	}
	i = -1;
	while (++i < mlx->win_y)
		mlx->y_ray[i] = (2. * (float)i - (float)mlx->win_y) * inv_x * t;
}

void	data_mlx_init(t_mlx	*mlx)
{
	mlx->win_x = 2560;
	mlx->win_y = 1395;
	mlx->fov = 60.;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x,
			mlx->win_y, "Cub3D");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
	mlx->x_ray = malloc(mlx->win_x * sizeof(t_vec));
	mlx->y_ray = malloc(mlx->win_y * sizeof(double));
	fill_ray(mlx);
}

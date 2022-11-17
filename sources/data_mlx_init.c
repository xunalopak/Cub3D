/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_mlx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:06:22 by jalamell          #+#    #+#             */
/*   Updated: 2022/11/16 22:14:27 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_ray(t_mlx *mlx)
{
	int			i;
	float const	inv_x = 1. / (float)mlx->win_x;

	i = -1;
	while (++i < mlx->win_x)
		mlx->x_ray[i] = 2. * (float)i * inv_x - 1.;
	i = -1;
	while (++i < mlx->win_y)
		mlx->y_ray[i] = ((float)mlx->win_y - 2. * (float)i) * inv_x;
	mlx->z = 1. / tan(mlx->fov / 2.);
}

void	data_mlx_init(t_mlx	*mlx)
{
	mlx->win_x = WIN_WIDTH;
	mlx->win_y = WIN_HEIGHT;
	mlx->fov = 3.1415926535 * (PC_FOV / 180.);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x,
			mlx->win_y, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &(mlx->img.bpp),
			&(mlx->img.length), &(mlx->img.endian));
	mlx->x_ray = malloc(mlx->win_x * sizeof(double));
	mlx->y_ray = malloc(mlx->win_y * sizeof(double));
	fill_ray(mlx);
}

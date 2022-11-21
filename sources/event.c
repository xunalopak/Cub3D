/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:15:47 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/21 19:33:55 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->player.move = MOVE_UP;
	else if (key == KEY_S || key == KEY_DOWN)
		data->player.move = MOVE_DOWN;
	else if (key == KEY_A)
		data->player.turn = ROTATE_LEFT;
	else if (key == KEY_D)
		data->player.turn = ROTATE_RIGHT;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		cleanup(data);
	else if (key == KEY_W || key == KEY_UP || key == KEY_S
		|| key == KEY_DOWN)
		data->player.move = 0;
	else if (key == KEY_A || key == KEY_LEFT || key == KEY_D
		|| key == KEY_RIGHT)
		data->player.turn = 0;
	return (0);
}

int	destroy_hook(t_data *data)
{
	ft_exit(0, data);
	return (0);
}

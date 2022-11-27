/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:15:47 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/27 22:06:25 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->player.move_u = MOVE_UP;
	else if (key == KEY_S || key == KEY_DOWN)
		data->player.move_d = MOVE_DOWN;
	else if (key == KEY_D || key == KEY_RIGHT)
		data->player.move_r = MOVE_RIGHT;
	else if (key == KEY_A || key == KEY_LEFT)
		data->player.move_l = MOVE_LEFT;
	else if (key == KEY_Q)
		data->player.turn_l = ROTATE_LEFT;
	else if (key == KEY_E)
		data->player.turn_r = ROTATE_RIGHT;
	else if (key == KEY_SPC && data->player.height < PC_HEIGHT + .0001)
		data->player.jmp = JMP;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		cleanup(data);
	else if (key == KEY_W || key == KEY_UP)
		data->player.move_u = 0;
	else if (key == KEY_S || key == KEY_DOWN)
		data->player.move_d = 0;
	else if (key == KEY_D || key == KEY_RIGHT)
		data->player.move_r = 0;
	else if (key == KEY_A || key == KEY_LEFT)
		data->player.move_l = 0;
	else if (key == KEY_Q)
		data->player.turn_l = 0;
	else if (key == KEY_E)
		data->player.turn_r = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	data->player.rot += (double)(x - data->player.mouse_x) * 0.01;
	data->player.mouse_x = x;
	return (0);
}

int	destroy_hook(t_data *data)
{
	ft_exit(0, data);
	return (0);
}

int	game_loop(t_data *data)
{
	t_vec	move;

	move.x = 0.;
	move.y = 0.;
	if (data->player.move_u == MOVE_UP)
		move.x += WALK_SPEED;
	if (data->player.move_d == MOVE_DOWN)
		move.x += -WALK_SPEED;
	if (data->player.move_l == MOVE_LEFT)
		move.y += -WALK_SPEED;
	if (data->player.move_r == MOVE_RIGHT)
		move.y += WALK_SPEED;
	move = vec_rot(&move, cos(data->player.rot), sin(data->player.rot));
	check_colition(data, &move);
	data->player.jmp -= ACC;
	data->player.height += data->player.jmp;
	if (data->player.height < .5)
		data->player.height = .5;
	vec_add(&(data->player.pos), move);
	if (data->player.turn_r == ROTATE_RIGHT)
		data->player.rot += TURN_SPEED;
	if (data->player.turn_l == ROTATE_LEFT)
		data->player.rot -= TURN_SPEED;
	render(data);
	return (0);
}

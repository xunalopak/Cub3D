/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:15:47 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/23 15:44:16 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->player.move = MOVE_UP;
	else if (key == KEY_S || key == KEY_DOWN)
		data->player.move = MOVE_DOWN;
	else if (key == KEY_D || key == KEY_RIGHT)
		data->player.move = MOVE_RIGHT;
	else if (key == KEY_A || key == KEY_LEFT)
		data->player.move = MOVE_LEFT;
	else if (key == KEY_Q)
		data->player.turn = ROTATE_LEFT;
	else if (key == KEY_E)
		data->player.turn = ROTATE_RIGHT;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		cleanup(data);
	else if (key == KEY_W || key == KEY_UP || key == KEY_S
		|| key == KEY_DOWN || key == KEY_A || key == KEY_LEFT
		|| key == KEY_D || key == KEY_RIGHT)
		data->player.move = 0;
	else if (key == KEY_Q || key == KEY_E)
		data->player.turn = 0;
	return (0);
}

int	destroy_hook(t_data *data)
{
	ft_exit(0, data);
	return (0);
}

static void	check_colition(t_data *data, t_vec *move)
{
	int	x;
	int	y;

	x = (int)floor(data->player.pos.x + move->x);
	y = (int)floor(data->player.pos.y);
	if (data->map.map[y][x] != '0')
		move->x = 0;
	x = (int)floor(data->player.pos.x);
	y = (int)floor(data->player.pos.y + move->y);
	if (data->map.map[y][x] != '0')
		move->y = 0;
	x = (int)floor(data->player.pos.x + move->x);
	y = (int)floor(data->player.pos.y + move->y);
	if (data->map.map[y][x] != '0')
		move->x = 0;
}

int	game_loop(t_data *data)
{
	t_vec	move;

	move.x = 0.;
	move.y = 0.;
	if (data->player.move == MOVE_UP)
		move.x = WALK_SPEED;
	if (data->player.move == MOVE_DOWN)
		move.x = -WALK_SPEED;
	if (data->player.move == MOVE_LEFT)
		move.y = -WALK_SPEED;
	if (data->player.move == MOVE_RIGHT)
		move.y = WALK_SPEED;
	move = vec_rot(&move, cos(data->player.rot), sin(data->player.rot));
	check_colition(data, &move);
	vec_add(&(data->player.pos), move);
	if (data->player.turn == ROTATE_RIGHT)
		data->player.rot += TURN_SPEED;
	if (data->player.turn == ROTATE_LEFT)
		data->player.rot -= TURN_SPEED;
	render(data);
	return (0);
}

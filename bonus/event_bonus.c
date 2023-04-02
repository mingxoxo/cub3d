/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:26 by wonyang           #+#    #+#             */
/*   Updated: 2023/04/02 17:55:33 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	exit_game(t_param *param)
{
	ft_free_param(param);
	exit(0);
}

int	key_release(int key, t_param *param)
{
	if (0 <= key && key < 256)
		param->key[key] = 0;
	return (0);
}

void	change_door_status(t_param *param)
{
	const int	pos[2] = {(int)param->ray.pos_x, (int)param->ray.pos_y};
	const int	dx[4] = {1, -1, 0, 0};
	const int	dy[4] = {0, 0, 1, -1};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (pos[X] + dx[i] < 0 || pos[X] + dx[i] >= param->map.height \
		|| pos[Y] + dy[i] < 0 || pos[Y] + dy[i] >= param->map.width)
		{
			i++;
			continue ;
		}
		if (param->map.arr[pos[X] + dx[i]][pos[Y] + dy[i]] == 'D')
			param->map.arr[pos[X] + dx[i]][pos[Y] + dy[i]] = 'O';
		else if (param->map.arr[pos[X] + dx[i]][pos[Y] + dy[i]] == 'O')
			param->map.arr[pos[X] + dx[i]][pos[Y] + dy[i]] = 'D';
		i++;
	}
}

int	key_press(int key, t_param *param)
{
	if (0 <= key && key < 256)
		param->key[key] = 1;
	if (key == KEY_SPACE)
		change_door_status(param);
	return (0);
}

int	mouse_move(int x, int y, t_param *param)
{
	param->mouse[X] = x;
	param->mouse[Y] = y;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:26 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/26 17:40:04 by wonyang          ###   ########seoul.kr  */
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

int	key_press(int key, t_param *param)
{
	if (0 <= key && key < 256)
		param->key[key] = 1;
	return (0);
}

int	mouse_move(int x, int y, t_param *param)
{
	param->mouse[X] = x;
	param->mouse[Y] = y;
	return (0);
}

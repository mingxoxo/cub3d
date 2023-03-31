/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:53:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/31 17:43:41 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

static int	get_sprite_count(t_param *param)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = 0;
	while (i < param->map.height)
	{
		j = 0;
		while (j < param->map.width)
		{
			if (param->map.arr[i][j] == 'A')
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
}

static void	get_sprite_coor(t_param *param)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = 0;
	while (i < param->map.height)
	{
		j = 0;
		while (j < param->map.width)
		{
			if (param->map.arr[i][j] == 'A')
			{
				param->spr.arr[cnt].x = j + 0.5;
				param->spr.arr[cnt].y = i + 0.5;
				cnt++;
			}
			j++;
		}
		i++;
	}
}

void	init_sprite(t_param *param)
{
	const int	cnt = get_sprite_count(param);

	param->spr.arr = (t_coor *)malloc(sizeof(t_coor) * cnt);
	param->spr.sp_cnt = cnt;
	if (param->spr.arr == NULL)
		ft_perror_exit("param: sprite", param);
	get_sprite_coor(param);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:53:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/04/01 16:19:06 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
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
				param->spr.arr[cnt].x = i + 0.5;
				param->spr.arr[cnt].y = j + 0.5;
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

static void	set_sprite_distance(t_param *param, t_coor *arr)
{
	const double	px = param->ray.pos_x;
	const double	py = param->ray.pos_y;
	int				i;

	i = 0;
	while (i < param->spr.sp_cnt)
	{
		arr[i].s_dst = pow(px - arr[i].x, 2) + pow(py - arr[i].y, 2);
		i++;
	}
}

void	sort_sprite(t_param	*param)
{
	t_coor			*arr;
	int				i;
	int				j;
	t_coor			tmp;

	arr = param->spr.arr;
	set_sprite_distance(param, arr);
	i = 0;
	while (i < param->spr.sp_cnt - 1)
	{
		j = i + 1;
		while (j < param->spr.sp_cnt)
		{
			if (arr[i].s_dst < arr[j].s_dst)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

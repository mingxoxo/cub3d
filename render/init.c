/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:23:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/20 19:20:30 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_param *param)
{
	param->ray.pos_x = param->map.sx;
	param->ray.pos_y = param->map.sy;
	param->ray.dir_x = -1; // todo : 플레이어 초기 방향으로 수정
	param->ray.dir_y = 0;
	param->ray.plane_x = 0;
	param->ray.plane_y = 0.66;
}

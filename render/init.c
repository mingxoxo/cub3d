/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:23:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/19 20:29:59 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_param *param)
{
	param->ray.posX = param->map.sx;
	param->ray.posY = param->map.sy;
	param->ray.dirX = -1; // todo : 플레이어 초기 방향으로 수정
	param->ray.dirY = 0;
	param->ray.planeX = 0;
	param->ray.planeY = 0.66;
}

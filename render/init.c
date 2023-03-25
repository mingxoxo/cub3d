/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:23:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/26 00:35:27 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_param *param, double x, double y)
{
	param->ray.dir_x = x;
	param->ray.dir_y = y;
}

static void	set_plane(t_param *param, double x, double y)
{
	param->ray.plane_x = x;
	param->ray.plane_y = y;
}

void	init_ray(t_param *param)
{
	param->ray.pos_x = param->map.sx + 0.5;
	param->ray.pos_y = param->map.sy + 0.5;
	if (param->map.sdir == 'E')
	{
		set_dir(param, 0, 1);
		set_plane(param, 0.66, 0);
	}
	else if (param->map.sdir == 'W')
	{
		set_dir(param, 0, -1);
		set_plane(param, -0.66, 0);
	}
	else if (param->map.sdir == 'N')
	{
		set_dir(param, -1, 0);
		set_plane(param, 0, 0.66);
	}
	else
	{
		set_dir(param, 1, 0);
		set_plane(param, 0, -0.66);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:13:11 by wonyang           #+#    #+#             */
/*   Updated: 2023/04/04 17:50:54 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_screen(t_param *param)
{
	int		x;
	double	camera_x;
	t_dda	dda;
	double	buf[WIN_WIDTH];

	mlx_clear_window(param->mlx.mlx, param->mlx.win);
	fill_background(param->mlx, param->info.f.rgb, param->info.c.rgb);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		dda.ray_dir[X] = param->ray.dir_x + param->ray.plane_x * camera_x;
		dda.ray_dir[Y] = param->ray.dir_y + param->ray.plane_y * camera_x;
		draw_line(param, &dda, x);
		buf[x] = dda.w_dst;
		x++;
	}
	sort_sprite(param);
	render_sprite(param, buf);
	draw_minimap(param);
	mlx_put_image_to_window(param->mlx.mlx, param->mlx.win, \
													param->mlx.img, 0, 0);
	if (param->frame == param->info.sp_cnt * 10000)
		param->frame = 0;
}

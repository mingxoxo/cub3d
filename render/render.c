/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:13:11 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/21 18:48:42 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

// void debug_dda(t_dda *dda)
// {
//     printf("ray_dir: (%f, %f), ", dda->ray_dir[0], dda->ray_dir[1]);
//     printf("map: (%d, %d), ", dda->map[0], dda->map[1]);
//     printf("side_dst: (%f, %f), ", dda->side_dst[0], dda->side_dst[1]);
//     printf("delta_dst: (%f, %f), ", dda->delta_dst[0], dda->delta_dst[1]);
//     printf("step: (%d, %d) ", dda->step[0], dda->step[1]);
// }

static void	set_dda(t_ray ray, t_dda *dda)
{
	dda->map[X] = (int)ray.pos_x;
	dda->map[Y] = (int)ray.pos_y;
	dda->delta_dst[X] = fabs(1 / dda->ray_dir[X]);
	dda->delta_dst[Y] = fabs(1 / dda->ray_dir[Y]);
	if (dda->ray_dir[X] < 0)
	{
		dda->step[X] = -1;
		dda->side_dst[X] = (ray.pos_x - dda->map[X]) * dda->delta_dst[X];
	}
	else
	{
		dda->step[X] = 1;
		dda->side_dst[X] = (dda->map[X] + 1.0 - ray.pos_x) * dda->delta_dst[X];
	}
	if (dda->ray_dir[Y] < 0)
	{
		dda->step[Y] = -1;
		dda->side_dst[Y] = (ray.pos_y - dda->map[Y]) * dda->delta_dst[Y];
	}
	else
	{
		dda->step[Y] = 1;
		dda->side_dst[Y] = (dda->map[Y] + 1.0 - ray.pos_y) * dda->delta_dst[Y];
	}
}

static double	get_wall_dst(t_param *p, t_dda *d)
{
	int		side;
	double	x_dst;

	//todo
	while (p->map.arr[d->map[X]][d->map[Y]] == '0' || p->map.arr[d->map[X]][d->map[Y]] == 'N')
	{
		if (d->side_dst[X] < d->side_dst[Y])
		{
			d->side_dst[X] += d->delta_dst[X];
			d->map[X] += d->step[X];
			side = 0;
		}
		else
		{
			d->side_dst[Y] += d->delta_dst[Y];
			d->map[Y] += d->step[Y];
			side = 1;
		}
	}
	if (side == 0)
	{
		x_dst = d->map[X] - p->ray.pos_x + (1 - d->step[X]) / 2;
		return (x_dst / d->ray_dir[X]);
	}
	return ((d->map[Y] - p->ray.pos_y + (1 - d->step[Y]) / 2) / d->ray_dir[Y]);
}

static void	draw_line(t_param *param, t_dda dda, double wall_dst, int x)
{
	int	line_height;
	int	draw[2];

	line_height = (int)(WIN_HEIGHT / wall_dst);
	draw[0] = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_height / 2 + WIN_HEIGHT / 2;
	if (draw[1] >= WIN_HEIGHT)
		draw[1] = WIN_HEIGHT - 1;

	//벽 색깔 선택
	char *color = "0x814202";
	// switch(param->map.arr[dda.map[X]][dda.map[Y]])
	// {
	// 	case 1:  color = "0x810202";  break; //red
	// 	case 2:  color = "0x028102";  break; //green
	// 	case 3:  color = "0x020281";   break; //blue
	// 	case 4:  color = NULL;  break; //white
	// 	default: color = "0x814202"; break; //yellow
	// }
	print_line(param->mlx, x, draw, color);
}

void	render_screen(t_param *param)
{
	int		x;
	double	camera_x;
	t_dda	dda;
	double	dst;

	fill_background(param->mlx);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		dda.ray_dir[X] = param->ray.dir_x + param->ray.plane_x * camera_x;
		dda.ray_dir[Y] = param->ray.dir_y + param->ray.plane_y * camera_x;
		set_dda(param->ray, &dda);
		dst = get_wall_dst(param, &dda);
		draw_line(param, dda, dst, x);
		x++;
	}
	mlx_put_image_to_window(param->mlx.mlx, param->mlx.win, \
													param->mlx.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:15:09 by wonyang           #+#    #+#             */
/*   Updated: 2023/04/02 16:55:05 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "cub3d_bonus.h"

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

static void	get_wall_dst(t_param *p, t_dda *d)
{
	double	x_dst;
	t_ray	r;

	r = p->ray;
	while (p->map.arr[d->map[X]][d->map[Y]] != '1'
		&& p->map.arr[d->map[X]][d->map[Y]] != 'D')
	{
		if (d->side_dst[X] < d->side_dst[Y])
		{
			d->side_dst[X] += d->delta_dst[X];
			d->map[X] += d->step[X];
			d->side = 0;
			continue ;
		}
		d->side_dst[Y] += d->delta_dst[Y];
		d->map[Y] += d->step[Y];
		d->side = 1;
	}
	if (d->side == 0)
	{
		x_dst = d->map[X] - r.pos_x + (1 - d->step[X]) / 2;
		d->w_dst = x_dst / d->ray_dir[X];
		return ;
	}
	d->w_dst = (d->map[Y] - r.pos_y + (1 - d->step[Y]) / 2) / d->ray_dir[Y];
}

static void	get_length_img(t_param *param, t_dda *dda)
{
	dda->l_height = (int)(WIN_HEIGHT / dda->w_dst);
	dda->draw[0] = -dda->l_height / 2 + WIN_HEIGHT / 2;
	if (dda->draw[0] < 0)
		dda->draw[0] = 0;
	dda->draw[1] = dda->l_height / 2 + WIN_HEIGHT / 2;
	if (dda->draw[1] >= WIN_HEIGHT)
		dda->draw[1] = WIN_HEIGHT - 1;
	if (param->map.arr[dda->map[X]][dda->map[Y]] == 'D')
		dda->img = param->info.d[0];
	else if (dda->side == 0 && dda->ray_dir[X] > 0)
		dda->img = param->info.no;
	else if (dda->side == 0 && dda->ray_dir[X] <= 0)
		dda->img = param->info.so;
	else if (dda->side == 1 && dda->ray_dir[Y] < 0)
		dda->img = param->info.ea;
	else
		dda->img = param->info.we;
}

static void	get_tex(t_param *param, t_dda *dda)
{
	double	wall;

	if (dda->side == 0)
		wall = param->ray.pos_y + dda->w_dst * dda->ray_dir[Y];
	else
		wall = param->ray.pos_x + dda->w_dst * dda->ray_dir[X];
	wall -= floor(wall);
	dda->tex[X] = (int)(wall * (double)dda->img.w);
	if (dda->side == 0 && dda->ray_dir[X] > 0)
		dda->tex[X] = dda->img.w - dda->tex[X] - 1;
	if (dda->side == 1 && dda->ray_dir[Y] < 0)
		dda->tex[X] = dda->img.w - dda->tex[X] - 1;
}

void	draw_line(t_param *param, t_dda *d, int x)
{
	double		step;
	double		tex_pos;
	int			y;
	uint32_t	color;

	set_dda(param->ray, d);
	get_wall_dst(param, d);
	get_length_img(param, d);
	get_tex(param, d);
	step = 1.0 * d->img.h / d->l_height;
	tex_pos = (d->draw[0] - WIN_HEIGHT / 2 + d->l_height / 2) * step;
	y = d->draw[0];
	while (y < d->draw[1])
	{
		d->tex[Y] = (int)tex_pos % d->img.h;
		tex_pos += step;
		color = ((uint32_t *)d->img.data)[d->img.h * d->tex[Y] + d->tex[X]];
		print_dot(param->mlx, x, y, color);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:13:11 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/26 00:29:17 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

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
	int		side;
	double	x_dst;

	while (p->map.arr[d->map[X]][d->map[Y]] == '0')
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
	d->side = side;
	if (side == 0)
	{
		x_dst = d->map[X] - p->ray.pos_x + (1 - d->step[X]) / 2;
		d->wall_dst = x_dst / d->ray_dir[X];
		return ;
	}
	d->wall_dst = (d->map[Y] - p->ray.pos_y + (1 - d->step[Y]) / 2) / d->ray_dir[Y];
}

static void	draw_line(t_param *param, t_dda dda, int x)
{
	int	line_height;
	int	draw[2];

	line_height = (int)(WIN_HEIGHT / dda.wall_dst);
	draw[0] = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_height / 2 + WIN_HEIGHT / 2;
	if (draw[1] >= WIN_HEIGHT)
		draw[1] = WIN_HEIGHT - 1;

	double	wall;
	int		tex[2];

	t_img	img;

	if (dda.side == 0 && dda.ray_dir[X] > 0)
		img = param->info.so;
	else if (dda.side == 0 && dda.ray_dir[X] <= 0)
		img = param->info.no;
	else if (dda.side == 1 && dda.ray_dir[Y] < 0)
		img = param->info.we;
	else
		img = param->info.ea;

	if (dda.side == 0)
		wall = param->ray.pos_y + dda.wall_dst * dda.ray_dir[Y];
	else
		wall = param->ray.pos_x + dda.wall_dst * dda.ray_dir[X];
	wall -= floor(wall);
	tex[X] = (int)(wall * (double)img.w);
	if (dda.side == 0 && dda.ray_dir[X] > 0)
		tex[X] = img.w - tex[X] - 1;
	if (dda.side == 1 && dda.ray_dir[Y] < 0)
		tex[X] = img.w - tex[X] - 1;
	
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	step = 1.0 * img.h / line_height;
	tex_pos = (draw[0] - WIN_HEIGHT / 2 + line_height / 2) * step;
	y = draw[0];
	while (y < draw[1])
	{
		tex[Y] = (int)tex_pos % img.h;
		tex_pos += step;
		color = ((unsigned int *)img.data)[img.h * tex[Y] + tex[X]];
		print_dot(param->mlx, x, y, color);
		y++;
	}
}

void	render_screen(t_param *param)
{
	int		x;
	double	camera_x;
	t_dda	dda;
	double	dst;

	fill_background(param->mlx, param->info.f.rgb, param->info.c.rgb);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		dda.ray_dir[X] = param->ray.dir_x + param->ray.plane_x * camera_x;
		dda.ray_dir[Y] = param->ray.dir_y + param->ray.plane_y * camera_x;
		set_dda(param->ray, &dda);
		get_wall_dst(param, &dda);
		draw_line(param, dda, x);
		x++;
	}
	mlx_put_image_to_window(param->mlx.mlx, param->mlx.win, \
													param->mlx.img, 0, 0);
}

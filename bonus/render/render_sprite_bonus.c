/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:50:41 by wonyang           #+#    #+#             */
/*   Updated: 2023/04/04 17:51:25 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static void	set_tf_screen(t_param *param, t_spc *sp, int i)
{
	const t_ray		r = param->ray;
	const double	sp_x = param->spr.arr[i].x - r.pos_x;
	const double	sp_y = param->spr.arr[i].y - r.pos_y;
	const double	i_det = 1.0 / (r.plane_x * r.dir_y - r.dir_x * r.plane_y);

	sp->tf[X] = i_det * (r.dir_y * sp_x - r.dir_x * sp_y);
	sp->tf[Y] = i_det * (-r.plane_y * sp_x + r.plane_x * sp_y);
	sp->s_scn = (int)((WIN_WIDTH / 2) * (1 + sp->tf[X] / sp->tf[Y]));
}

static void	set_sprite_size(t_spc *sp)
{
	const int		u_div = 1;
	const int		v_div = 1;
	const double	v_move = 0.0;

	sp->m_scn = (int)(v_move / sp->tf[Y]);
	sp->s_height = (int)fabs(WIN_HEIGHT / sp->tf[Y]) / v_div;
	sp->d_start[Y] = -sp->s_height / 2 + WIN_HEIGHT / 2 + sp->m_scn;
	if (sp->d_start[Y] < 0)
		sp->d_start[Y] = 0;
	sp->d_end[Y] = sp->s_height / 2 + WIN_HEIGHT / 2 + sp->m_scn;
	if (sp->d_end[Y] >= WIN_HEIGHT)
		sp->d_end[Y] = WIN_HEIGHT - 1;
	sp->s_width = (int)fabs(WIN_HEIGHT / sp->tf[Y]) / u_div;
	sp->d_start[X] = -sp->s_width / 2 + sp->s_scn;
	if (sp->d_start[X] < 0)
		sp->d_start[X] = 0;
	sp->d_end[X] = sp->s_width / 2 + sp->s_scn;
	if (sp->d_end[X] >= WIN_WIDTH)
		sp->d_end[X] = WIN_WIDTH - 1;
}

static void	print_sprite_dot(int x, int y, t_param *param, t_spc sp)
{
	uint32_t	color;

	if (sp.tex[X] >= 0 && sp.tex[X] < sp.img.w \
		&& sp.tex[Y] >= 0 && sp.tex[Y] < sp.img.h)
	{
		color = ((uint32_t *)sp.img.data)[sp.img.w * sp.tex[Y] + sp.tex[X]];
		if (color != 0xFFFFFF)
			print_dot(param->mlx, x, y, color);
	}
}

static void	draw_sprite(t_param *param, t_spc sp, double buf[WIN_WIDTH])
{
	int			x;
	int			y;
	int			d;

	x = sp.d_start[X];
	while (x < sp.d_end[X])
	{
		sp.tex[X] = (int)(256 * (x - (-sp.s_width / 2 + sp.s_scn)) \
												* sp.img.w / sp.s_width) / 256;
		y = sp.d_start[Y];
		if (sp.tf[Y] <= 0 || buf[x] <= sp.tf[Y])
			y = sp.d_end[Y];
		while (y < sp.d_end[Y])
		{
			d = (y - sp.m_scn) * 256 - WIN_HEIGHT * 128 + sp.s_height * 128;
			sp.tex[Y] = ((d * sp.img.h) / sp.s_height) / 256;
			print_sprite_dot(x, y, param, sp);
			y++;
		}
		x++;
	}
}

void	render_sprite(t_param *param, double buf[WIN_WIDTH])
{
	int		i;
	t_spc	sp;

	if (param->spr.sp_cnt == 0)
		return ;
	sp.img = param->info.sp[param->frame / 10 % param->info.sp_cnt];
	i = 0;
	while (i < param->spr.sp_cnt)
	{
		set_tf_screen(param, &sp, i);
		set_sprite_size(&sp);
		draw_sprite(param, sp, buf);
		i++;
	}
}

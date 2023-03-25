/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:35:05 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 02:27:29 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

static void	move_front_back(t_param *param, const double ms, int keycode)
{
	t_ray	*ray;
	char	**map;

	ray = &(param->ray);
	map = param->map.arr;
	if (keycode == KEY_W)
	{
		if (map[(int)(ray->pos_x + ray->dir_x * ms)][(int)(ray->pos_y)] == '0')
			ray->pos_x += ray->dir_x * ms;
		if (map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ms)] == '0')
			ray->pos_y += ray->dir_y * ms;
	}
	else if (keycode == KEY_S)
	{
		if (map[(int)(ray->pos_x - ray->dir_x * ms)][(int)(ray->pos_y)] == '0')
			ray->pos_x -= ray->dir_x * ms;
		if (map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ms)] == '0')
			ray->pos_y -= ray->dir_y * ms;
	}
}

static void	move_left_right(t_param *param, const double ms, int keycode)
{
	t_ray	*ray;
	char	**map;

	ray = &(param->ray);
	map = param->map.arr;
	if (keycode == KEY_A)
	{
		if (map[(int)(ray->pos_x - ray->dir_y * ms)][(int)(ray->pos_y)] == '0')
			ray->pos_x -= ray->dir_y * ms;
		if (map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_x * ms)] == '0')
			ray->pos_y += ray->dir_x * ms;
	}
	else if (keycode == KEY_D)
	{
		if (map[(int)(ray->pos_x + ray->dir_y * ms)][(int)(ray->pos_y)] == '0')
			ray->pos_x += ray->dir_y * ms;
		if (map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_x * ms)] == '0')
			ray->pos_y -= ray->dir_x * ms;
	}
}

static void	rotate_right(t_ray *ray, const double rs)
{
	const double	old_dir = ray->dir_x;
	const double	old_plane = ray->plane_x;

	ray->dir_x = ray->dir_x * cos(-rs) - ray->dir_y * sin(-rs);
	ray->dir_y = old_dir * sin(-rs) + ray->dir_y * cos(-rs);
	ray->plane_x = ray->plane_x * cos(-rs) - ray->plane_y * sin(-rs);
	ray->plane_y = old_plane * sin(-rs) + ray->plane_y * cos(-rs);
}

static void	rotate_left(t_ray *ray, const double rs)
{
	const double	old_dir = ray->dir_x;
	const double	old_plane = ray->plane_x;

	ray->dir_x = ray->dir_x * cos(rs) - ray->dir_y * sin(rs);
	ray->dir_y = old_dir * sin(rs) + ray->dir_y * cos(rs);
	ray->plane_x = ray->plane_x * cos(rs) - ray->plane_y * sin(rs);
	ray->plane_y = old_plane * sin(rs) + ray->plane_y * cos(rs);
}

int	key_press(int key, t_param *param)
{
	const double	move_speed = 0.1 * 1.0;
	const double	rot_speed = 0.1 * 1.0;

	if (key == KEY_ESC)
		exit_game(param);
	else if (key == KEY_W || key == KEY_S)
		move_front_back(param, move_speed, key);
	else if (key == KEY_A || key == KEY_D)
		move_left_right(param, move_speed, key);
	else if (key == KEY_RIGHT)
		rotate_right(&(param->ray), rot_speed);
	else if (key == KEY_LEFT)
		rotate_left(&(param->ray), rot_speed);
	render_screen(param);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:35:05 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/21 19:29:10 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

void	move_front(t_param *param, const double move_speed)
{
	t_ray	*ray;
	char	**map;

	ray = &(param->ray);
	map = param->map.arr;
	if(map[(int)(ray->pos_x + ray->dir_x * move_speed)][(int)(ray->pos_y)] == '0')
		ray->pos_x += ray->dir_x * move_speed;
	if(map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * move_speed)] == '0')
		ray->pos_y += ray->dir_y * move_speed;
}

void	move_back(t_param *param, const double move_speed)
{
	t_ray	*ray;
	char	**map;

	ray = &(param->ray);
	map = param->map.arr;
	if(map[(int)(ray->pos_x - ray->dir_x * move_speed)][(int)(ray->pos_y)] == '0')
		ray->pos_x -= ray->dir_x * move_speed;
	if(map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * move_speed)] == '0')
		ray->pos_y -= ray->dir_y * move_speed;
}

void	rotate_right(t_ray *ray, const double rot_speed)
{
	const double	oldDirX = ray->dir_x;
	const double	oldPlaneX = ray->plane_x;

	ray->dir_x = ray->dir_x * cos(-rot_speed) - ray->dir_y * sin(-rot_speed);
	ray->dir_y = oldDirX * sin(-rot_speed) + ray->dir_y * cos(-rot_speed);
	ray->plane_x = ray->plane_x * cos(-rot_speed) - ray->plane_y * sin(-rot_speed);
	ray->plane_y = oldPlaneX * sin(-rot_speed) + ray->plane_y * cos(-rot_speed);
}

void	rotate_left(t_ray *ray, const double rot_speed)
{
	const double	oldDirX = ray->dir_x;
	const double	oldPlaneX = ray->plane_x;

	ray->dir_x = ray->dir_x * cos(rot_speed) - ray->dir_y * sin(rot_speed);
	ray->dir_y = oldDirX * sin(rot_speed) + ray->dir_y * cos(rot_speed);
	ray->plane_x = ray->plane_x * cos(rot_speed) - ray->plane_y * sin(rot_speed);
	ray->plane_y = oldPlaneX * sin(rot_speed) + ray->plane_y * cos(rot_speed);
}

int	key_press(int key, t_param *param)
{
	const double	move_speed = 0.1 * 0.7;
	const double	rot_speed = 0.1 * 1.0;

	if (key == KEY_ESC)
		exit_game(param);
	else if (key == KEY_W)
		move_front(param, move_speed);
	else if (key == KEY_S)
		move_back(param, move_speed);
	else if (key == KEY_RIGHT)
		rotate_right(&(param->ray), rot_speed);
	else if (key == KEY_LEFT)
		rotate_left(&(param->ray), rot_speed);
	render_screen(param);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:27:07 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/19 20:11:33 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_img(t_img *img)
{
	img->path = NULL;
	img->ptr = NULL;
	img->w = 0;
	img->h = 0;
}

static void	init_color(t_color *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		color->rgb[i] = 0;
		i++;
	}
	color->info = NULL;
}

static void	init_map(t_map *map)
{
	map->sx = -1;
	map->sy = -1;
	map->height = 0;
	map->width = 0;
	map->arr = NULL;
}

static void	init_mlx(t_param *param)
{
	param->mlx = NULL;
	param->win = NULL;
	param->mlx = mlx_init();
	if (!(param->mlx))
		ft_error_exit("mlx: mlx_ptr error\n", param);
	param->win = mlx_new_window(param->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!(param->win))
		ft_error_exit("mlx: win_ptr error\n", param);
}

void	init_param(t_param *param)
{
	init_img(&(param->info.no));
	init_img(&(param->info.so));
	init_img(&(param->info.we));
	init_img(&(param->info.ea));
	init_color(&(param->info.f));
	init_color(&(param->info.c));
	init_map(&param->map);
	init_mlx(param);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:27:07 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 02:54:29 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_img(t_img *img)
{
	img->ptr = NULL;
	img->path = NULL;
	img->data = NULL;
	img->w = 0;
	img->h = 0;
	img->lsize = 0;
	img->bpp = 0;
	img->end = 0;
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
	map->sdir = 0;
	map->height = 0;
	map->width = 0;
	map->arr = NULL;
}

static void	init_mlx(t_param *param)
{
	t_mlx	*mlx;

	mlx = &(param->mlx);
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->mlx = mlx_init();
	if (!(mlx->mlx))
		ft_error_exit("mlx: mlx_ptr error\n", param);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!(mlx->win))
		ft_error_exit("mlx: win_ptr error\n", param);
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->bit = 0;
	mlx->lsize = 0;
	mlx->end = 0;
	mlx->ptr = mlx_get_data_addr(mlx->img, &(mlx->bit), \
											&(mlx->lsize), &(mlx->end));
	if (!(mlx->ptr))
		ft_error_exit("mlx: ptr error\n", param);
}

void	init_param(t_param *param)
{
	int	i;

	i = 0;
	while (i < 256)
		param->key[i++] = 0;
	init_img(&(param->info.no));
	init_img(&(param->info.so));
	init_img(&(param->info.we));
	init_img(&(param->info.ea));
	init_color(&(param->info.f));
	init_color(&(param->info.c));
	init_map(&param->map);
	init_mlx(param);
}

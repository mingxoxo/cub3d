/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:27:07 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/14 23:02:12 by jeongmin         ###   ########.fr       */
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
	color->info = NULL;
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

static void	init_map(t_map *map)
{
	map->sx = -1;
	map->sy = -1;
	map->height = 0;
	map->width = 0;
	map->arr = NULL;
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
}

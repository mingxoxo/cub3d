/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/29 19:24:47 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

char	**ft_free_two_array(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = 0;
	return (0);
}

static void	ft_free_img(t_img *img, void *mlx)
{
	if (!img)
		return ;
	if (img->path)
		free(img->path);
	if (mlx && img->ptr)
		mlx_destroy_image(mlx, img->ptr);
}

static void	ft_free_color(t_color *color)
{
	if (!color)
		return ;
	if (color->info)
		free(color->info);
}

void	ft_free_param(t_param *param)
{
	int	i;
	
	if (!param)
		return ;
	if (param->map.arr)
		ft_free_two_array(&(param->map.arr));
	ft_free_img(&(param->info.no), param->mlx.mlx);
	ft_free_img(&(param->info.so), param->mlx.mlx);
	ft_free_img(&(param->info.we), param->mlx.mlx);
	ft_free_img(&(param->info.ea), param->mlx.mlx);
	ft_free_color(&(param->info.f));
	ft_free_color(&(param->info.c));
	if (param->info.d)
	{
		i = 0;
		while (i < param->info.d_cnt)
		{
			ft_free_img(param->info.d + i, param->mlx.mlx);
			i++;
		}
		free(param->info.d);
	}
	if (param->info.sp)
	{
		i = 0;
		while (i < param->info.sp_cnt)
		{
			ft_free_img(param->info.sp + i, param->mlx.mlx);
			i++;
		}
		free(param->info.sp);
	}
	if (param->mlx.mlx && param->mlx.win)
		mlx_destroy_window(param->mlx.mlx, param->mlx.win);
	return ;
}

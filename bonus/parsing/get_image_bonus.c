/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:45:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 23:42:06 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	file_to_image(t_img *img, t_param *param)
{
	img->ptr = mlx_xpm_file_to_image(param->mlx.mlx, img->path, \
									&(img->w), &(img->h));
	if (img->ptr == NULL)
		ft_perror_exit("mlx: img load error", param);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->lsize, &img->end);
	if (img->data == NULL)
		ft_perror_exit("mlx: img load error", param);
}

static void	get_image_arr(t_img *img, int cnt, t_param *param)
{
	int		i;

	i = 0;
	while (i < cnt)
	{
		file_to_image(img + i, param);
		i++;
	}
}

void	get_image(t_param *param)
{
	file_to_image(&(param->info.no), param);
	file_to_image(&(param->info.so), param);
	file_to_image(&(param->info.we), param);
	file_to_image(&(param->info.ea), param);
	get_image_arr(param->info.d, param->info.d_cnt, param);
	get_image_arr(param->info.sp, param->info.sp_cnt, param);
}

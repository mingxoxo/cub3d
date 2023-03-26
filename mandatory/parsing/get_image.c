/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:45:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 23:32:40 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	get_image(t_param *param)
{
	file_to_image(&(param->info.no), param);
	file_to_image(&(param->info.so), param);
	file_to_image(&(param->info.we), param);
	file_to_image(&(param->info.ea), param);
}

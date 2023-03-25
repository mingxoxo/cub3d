/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:45:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/25 16:41:17 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_to_image(t_img *img, t_param *param)
{
	void	*ptr;

	ptr = mlx_xpm_file_to_image(param->mlx.mlx, img->path, \
									&(img->w), &(img->h));
	if (ptr == NULL)
		ft_perror_exit("mlx: img load error", param);
	img->data = mlx_get_data_addr(ptr, &img->bpp, &img->lsize, &img->end);
	if (img->data == NULL)
		ft_perror_exit("mlx: img load error", param);
	mlx_destroy_image(param->mlx.mlx, ptr);
}

void	get_image(t_param *param)
{
	file_to_image(&(param->info.no), param);
	file_to_image(&(param->info.so), param);
	file_to_image(&(param->info.we), param);
	file_to_image(&(param->info.ea), param);
}

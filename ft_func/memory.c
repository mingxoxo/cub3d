/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/15 21:37:57 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

void	*ft_malloc(size_t size, t_param *param)
{
	void	*new;

	new = malloc(size);
	if (!new)
		ft_perror_exit(NULL, param);
	return (new);
}

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

static void	ft_free_img(t_img *img)
{
	if (!img)
		return ;
	if (img->path)
		free(img->path);
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
	if (!param)
		return ;
	if (param->map.arr)
		ft_free_two_array(&(param->map.arr));
	ft_free_img(&(param->info.no));
	ft_free_img(&(param->info.so));
	ft_free_img(&(param->info.we));
	ft_free_img(&(param->info.ea));
	ft_free_color(&(param->info.f));
	ft_free_color(&(param->info.c));
	return ;
}

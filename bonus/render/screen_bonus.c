/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:25:46 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/29 21:33:17 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	create_argb(int a, int rgb[3])
{
	return (a << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	print_mini_rect(t_mlx mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			print_dot(mlx, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	print_dot(t_mlx mlx, int x, int y, int color)
{
	char	*dst;

	if (WIN_HEIGHT <= y || WIN_WIDTH <= x || x < 0 || y < 0)
		return ;
	dst = mlx.ptr + (y * (mlx.lsize) + x * (mlx.bit) / 8);
	*(unsigned int *)dst = color;
}

void	fill_background(t_mlx mlx, int c1[3], int c2[3])
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			dst = mlx.ptr + (i * (mlx.lsize) + j * (mlx.bit) / 8);
			if (i < WIN_HEIGHT / 2)
				*(unsigned int *)dst = create_argb(0, c1);
			else
				*(unsigned int *)dst = create_argb(0, c2);
			j++;
		}
		i++;
	}
}

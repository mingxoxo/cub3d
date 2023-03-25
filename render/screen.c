/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:25:46 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/25 17:01:01 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

static int	hex_to_int(char *hex)
{
	int	i;
	int	res;

	if (!hex || ft_strlen(hex) != 8)
		return (create_argb(0, 255, 255, 255));
	i = 2;
	res = 0;
	while (hex[i])
	{
		res <<= 4;
		if (ft_isdigit(hex[i]))
			res += hex[i] - '0';
		else
			res += ft_tolower(hex[i]) - 'a' + 10;
		i++;
	}
	return (res);
}

void	print_dot(t_mlx mlx, int x, int y, int color)
{
	char	*dst;

	if (WIN_HEIGHT <= y || WIN_WIDTH <= x || x < 0 || y < 0)
		return ;
	dst = mlx.ptr + (y * (mlx.lsize) + x * (mlx.bit) / 8);
	*(unsigned int *)dst = color;
}

// void	print_line(t_mlx mlx, int x, int draw[2], char *color)
// {
// 	int	i;

// 	// printf("%d %d\n", draw[0], draw[1]);
// 	i = draw[0];
// 	while (i <= draw[1])
// 	{
// 		print_dot(mlx, x, i, color);
// 		i++;
// 	}
// }

void	fill_background(t_mlx mlx)
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
				*(unsigned int *)dst = create_argb(0, 0, 255, 255); // sky
			else
				*(unsigned int *)dst = create_argb(0, 153, 204, 0); // ground
			j++;
		}
		i++;
	}
}

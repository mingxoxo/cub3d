/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:06:18 by jeongmin          #+#    #+#             */
/*   Updated: 2023/04/03 17:31:59 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static void	calc_start_cor(t_param *param, int s[2])
{
	int			min_w;
	int			min_h;
	const int	pos_x = floor(param->ray.pos_x);
	const int	pos_y = floor(param->ray.pos_y);

	s[X] = 0;
	s[Y] = 0;
	if (MINI_H < param->map.height)
	{
		min_h = ft_min(pos_x + MINI_H / 2 + 1, param->map.height) - MINI_H;
		s[Y] = ft_max(0, min_h);
	}
	if (MINI_W < param->map.width)
	{
		min_w = ft_min(pos_y + MINI_W / 2 + 1, param->map.width) - MINI_W;
		s[X] = ft_max(0, min_w);
	}
}

static void	print_view(t_mlx mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			print_dot(mlx, x + i + 3, y + j + 3, color);
			j++;
		}
		i++;
	}
}

static void	draw_player_view(t_mlx mlx, t_ray ray, int s[2])
{
	const int		pos_x = floor(ray.pos_x) - s[Y];
	const int		pos_y = floor(ray.pos_y) - s[X];
	const double	dir_x = ray.dir_x;
	const double	dir_y = ray.dir_y;

	print_mini_rect(mlx, pos_y * 10, pos_x * 10, 0xFF0000);
	print_view(mlx, (pos_y + dir_y) * 10, (pos_x + dir_x) * 10, 0x1FDA11);
}

static int	matching_color(char c)
{
	int			i;
	const char	*identifier = " 1DOA";
	const int	color[5] = {0x333333, 0x050099, 0x8B4513, 0xCC9966, 0xEE82EE};

	i = 0;
	while (i < 5)
	{
		if (c == identifier[i])
			return (color[i]);
		i++;
	}
	return (0xD5D5D5);
}

void	draw_minimap(t_param *param)
{
	int	i;
	int	j;
	int	color;
	int	s[2];

	calc_start_cor(param, s);
	i = 0;
	while (i < param->map.height && i < MINI_H)
	{
		j = 0;
		while (j < param->map.width && j < MINI_W)
		{
			color = matching_color(param->map.arr[i + s[Y]][j + s[X]]);
			print_mini_rect(param->mlx, j * 10, i * 10, color);
			j++;
		}
		i++;
	}
	draw_player_view(param->mlx, param->ray, s);
}

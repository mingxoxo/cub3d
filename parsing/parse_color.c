/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:53:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/03/17 16:17:50 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	str_to_int(char *str, int *n)
{
	char	*res;

	*n = ft_atoi(str);
	res = ft_itoa(*n);
	if (!res)
		return (ALLOC_FAILED);
	if (*str == '+')
		str++;
	if (ft_strcmp(str, res) != 0)
	{
		free(res);
		return (ERROR);
	}
	free(res);
	return (SUCCESS);
}

static int	parse_rgb(t_color *color)
{
	int		i;
	int		rgb[3];
	int		errno;
	char	**split;
	
	split = ft_split(color->info, ',');
	if (!split)
		return (ALLOC_FAILED);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		ft_free_two_array(&split);
		return (ERROR);
	}
	i = 0;
	while (i < 3)
	{
		errno = str_to_int(split[i], rgb + i);
		if (errno)
		{
			ft_free_two_array(&split);
			return (errno);
		}
		if (rgb[i] < 0 || 255 < rgb[i])
		{
			ft_free_two_array(&split);
			return (ERROR);
		}
		i++;
	}
	color->r = rgb[0];
	color->g = rgb[1];
	color->b = rgb[2];
	ft_free_two_array(&split);
	return (SUCCESS);
}

int	parse_color(t_info *info)
{
	int	errno;

	errno = parse_rgb(&(info->f));
	if (errno)
		return (errno);
	errno = parse_rgb(&(info->c));
	return (errno);
}

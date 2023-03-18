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

static int	error_handler(int errno, char ***split)
{
	ft_free_two_array(split);
	return (errno);
}

static int	parse_rgb(t_color *color)
{
	int		i;
	int		errno;
	char	**split;

	split = ft_split(color->info, ',');
	if (!split)
		return (ALLOC_FAILED);
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (error_handler(ERROR, &split));
	i = 0;
	while (i < 3)
	{
		errno = str_to_int(split[i], color->rgb + i);
		if (errno)
			return (error_handler(errno, &split));
		if (color->rgb[i] < 0 || 255 < color->rgb[i])
			return (error_handler(ERROR, &split));
		i++;
	}
	ft_free_two_array(&split);
	return (SUCCESS);
}

// debugging func
static void	print_color(t_color *color, char *name)
{
	int	i;

	i = 0;
	printf("-------------------------\n");
	printf("[%s]\n", name);
	while (i < 3)
	{
		printf("(%d)\n", color->rgb[i]);
		i++;
	}
}

int	parse_color(t_info *info)
{
	int	errno;

	errno = parse_rgb(&(info->f));
	print_color(&(info->f), "F");
	if (errno)
		return (errno);
	errno = parse_rgb(&(info->c));
	print_color(&(info->c), "C");
	return (errno);
}

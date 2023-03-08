/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/08 17:24:33 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_char(t_param *param, char **s)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	arr = param->map.arr;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("NSEW", arr[i][j]))
			{
				if (param->info.sx != -1 || param->info.sy != -1)
				{
					*s = "map: There must be one player.";
					return (1);
				}
				param->info.sy = i;
				param->info.sx = j;
			}
			else if (ft_strchr("01 ", arr[i][j]) == NULL)
			{
				*s = "map: The character must be 0, 1, N, S, E, W, or space.";
				return (1);
			}
			j++;
		}
		i++;
	}
	if (param->info.sx == -1 && param->info.sy == -1)
	{
		*s = "map: There must be one player.";
		return (1);
	}
	return (0);
}

void	check_map(t_param *param, t_list *lst)
{
	char	*s;

	s = NULL;
	if (check_char(param, &s))
	{
		ft_lstclear(&lst, free);
		ft_error_exit(s, param);
	}
}
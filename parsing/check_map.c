/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/09 17:44:08 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*check_char(t_info *info, char **arr)
{
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("NSEW", arr[i][j]))
			{
				if (info->sx != -1 || info->sy != -1)
					return ("map: There must be one player.");
				info->sy = i;
				info->sx = j;
			}
			else if (ft_strchr("01 ", arr[i][j]) == NULL)
				return ("map: The character must be  \
							  0, 1, N, S, E, W or space.");
			j++;
		}
		i++;
	}
	if (info->sx == -1 && info->sy == -1)
		return ("map: There must be one player.");
	return (0);
}

void	check_map(t_param *param, t_list *lst)
{
	char	*error_msg;

	error_msg = check_char(&(param->info), param->map.arr);
	if (error_msg)
	{
		ft_lstclear(&lst, free);
		ft_error_exit(error_msg, param);
	}
}

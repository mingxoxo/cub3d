/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/27 03:25:12 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_char_in_map(t_list *map_lst, char c)
{
	char	*line;

	while (map_lst)
	{
		line = (char *)(map_lst->content);
		if (ft_strchr(line, c))
			return (TRUE);
		map_lst = map_lst->next;
	}
	return (FALSE);
}

int	check_bonus(t_list *map_lst, t_list *d_lst, t_list *sp_lst)
{
	if (is_char_in_map(map_lst, 'D') && d_lst == NULL)
		return (ERROR);
	if (is_char_in_map(map_lst, 'A'))
	{
		if (sp_lst == NULL || sp_lst->next == NULL)
			return (ERROR);
	}
	return (SUCCESS);
}

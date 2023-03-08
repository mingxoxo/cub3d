/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/05 18:51:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

t_list	*ft_lstnew_cub(void *str, t_list *lst, t_param *param)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
	{
		ft_lstclear(&lst, free);
		ft_perror_exit(NULL, param);
	}
	return (new);
}

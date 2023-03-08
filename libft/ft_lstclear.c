/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 03:15:08 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/13 03:16:00 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*del_node;

	tmp = *lst;
	while (tmp)
	{
		del_node = tmp;
		tmp = tmp->next;
		if (del)
			(*del)(del_node->content);
		free(del_node);
	}
	*lst = 0;
}

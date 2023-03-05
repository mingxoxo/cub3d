/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 03:13:57 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:50:41 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_front(t_list **cmd)
{
	t_list	*del;

	del = (*cmd)->next;
	(*cmd)->next = del->next;
	free(del);
}

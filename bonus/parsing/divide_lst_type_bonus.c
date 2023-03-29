/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_lst_type_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:59:52 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/29 21:27:27 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_this_identifier(char *line, const char *identifier)
{
	int			len;

	if (line[0] == '\n')
		return (FALSE);
	while (*line == ' ')
	line++;
	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) == 0 && *(line + len) == ' ')
		return (TRUE);
	return (FALSE);
}

static t_list	*add_lst(t_list *tmp, t_list *prev, t_list **head, t_list **lst)
{
	if (prev)
		prev->next = tmp->next;
	else
		*head = tmp->next;
	tmp->next = NULL;
	ft_lstadd_back(lst, tmp);
	if (prev)
		return (prev->next);
	return (*head);
}

void	divide_lst_by_type(t_list **m_lst, t_list **d_lst, t_list **sp_lst)
{
	t_list	*prev;
	t_list	*tmp;

	prev = NULL;
	tmp = *m_lst;
	while (tmp)
	{
		if (is_this_identifier(tmp->content, "D"))
			tmp = add_lst(tmp, prev, m_lst, d_lst);
		else if (is_this_identifier(tmp->content, "SP"))
			tmp = add_lst(tmp, prev, m_lst, sp_lst);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

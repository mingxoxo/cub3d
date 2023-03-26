/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_lst_type_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:59:52 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 22:46:39 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_door(char *line)
{
	int			len;
	const char	*identifier = "D";

	if (line[0] == '\n')
		return (FALSE);
	while (*line == ' ')
	line++;
	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) == 0 && *(line + len) == ' ')
		return (TRUE);
	return (FALSE);
}

static int	is_sprite(char *line)
{
	int			len;
	const char	*identifier = "SP";

	if (line[0] == '\n')
		return (FALSE);
	while (*line == ' ')
	line++;
	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) == 0 && *(line + len) == ' ')
		return (TRUE);
	return (FALSE);
}

void	divide_lst_by_type(t_list **m_lst, t_list **d_lst, t_list **sp_lst)
{
	t_list	*prev;
	t_list	*lst;

	prev = NULL;
	lst = *m_lst;
	while (lst)
	{
		if (is_door(lst->content))
		{
			if (prev)
				prev->next = lst->next;
			else
				*m_lst = lst->next;
			lst->next = NULL;
			ft_lstadd_back(d_lst, lst);
			lst = prev->next;
		}
		else if (is_sprite(lst->content))
		{
			if (prev)
				prev->next = lst->next;
			else
				*m_lst = lst->next;
			prev->next = lst->next;
			lst->next = NULL;
			ft_lstadd_back(sp_lst, lst);
			lst = prev->next;
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
}
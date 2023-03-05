/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/05 19:09:40 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

static t_list	*read_map(char *filename, t_param *param)
{
	int		fd;
	char	*line;
	t_list	*lst;

	lst = NULL;
	fd = ft_open(filename, param);
	while (1)
	{
		if (get_next_line(fd, &line) == GFAIL)
		{
			ft_lstclear(&lst, free);
			ft_error_exit("get_next_line", param);
		}
		if (!line)
			break ;
		ft_lstadd_back(&lst, ft_lstnew_cub(line, lst, param));
	}
	ft_close(fd, param);
	return (lst);
}

static void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)(lst->content));
		lst = lst->next;
	}
}
char	**parse_map(char *filename, t_param *param)
{
	char	**arr;
	t_list	*lst;

	arr = NULL;
	lst = read_map(filename, param);
	print_lst(lst);
	// arr = cast_map(lst, param->map.h, param);
	ft_lstclear(&lst, NULL);
	return (arr);
}

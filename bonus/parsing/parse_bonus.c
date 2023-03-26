/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/27 03:29:25 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d_bonus.h"

static t_list	*read_file(char *filename, t_param *param)
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
		if (!line || line[0] == 0)
			break ;
		ft_lstadd_back(&lst, ft_lstnew_cub(line, lst, param));
	}
	ft_close(fd, param);
	return (lst);
}

static int	is_element(char *line)
{
	int			i;
	int			len;
	const char	identifier[8][3] = {"NO", "SO", "WE", "EA", "F", "C", "D", "SP"};

	if (line[0] == '\n')
		return (TRUE);
	while (*line == ' ')
		line++;
	i = 0;
	while (i < 8)
	{
		len = ft_strlen(identifier[i]);
		if (ft_strncmp(line, identifier[i], len) == 0 && *(line + len) == ' ')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static t_list	*divide_lst(t_list **head)
{
	t_list	*prev;
	t_list	*lst;

	prev = NULL;
	lst = *head;
	while (lst)
	{
		if (!is_element(lst->content))
			break ;
		prev = lst;
		lst = lst->next;
	}
	if (prev)
		prev->next = NULL;
	else
		*head = NULL;
	return (lst);
}

static void	check_error(int errno, t_list *lst[4], t_param *param)
{
	if (!errno)
		return ;
	ft_lstclear(&(lst[0]), free);
	ft_lstclear(&(lst[1]), free);
	ft_lstclear(&(lst[2]), free);
	ft_lstclear(&(lst[3]), free);
	if (errno == ERROR)
		ft_error_exit("element: The input format is invalid", param);
	else
		ft_perror_exit("param: element", param);
}

void	parse(char *filename, t_param *param)
{
	int		errno;
	t_list	*lst[4];

	lst[0] = read_file(filename, param);
	lst[1] = divide_lst(lst);
	lst[2] = NULL;
	lst[3] = NULL;
	divide_lst_by_type(lst, lst + 2, lst + 3);
	errno = check_bonus(lst[1], lst[2], lst[3]);
	check_error(errno, lst, param);
	errno = parse_info(lst[0], param);
	check_error(errno, lst, param);
	errno = parse_color(&(param->info));
	check_error(errno, lst, param);
	errno = parse_info_bonus(lst[2], &(param->info.d), &(param->info.d_cnt));
	check_error(errno, lst, param);
	errno = parse_info_bonus(lst[3], &(param->info.sp), &(param->info.sp_cnt));
	check_error(errno, lst, param);
	ft_lstclear(&(lst[0]), free);
	ft_lstclear(&(lst[2]), free);
	ft_lstclear(&(lst[3]), free);
	parse_map(lst[1], param);
	get_image(param);
}

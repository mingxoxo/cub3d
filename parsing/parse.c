/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/16 20:39:51 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

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
	const char	identifier[6][3] = {"NO", "SO", "WE", "EA", "F", "C"};

	if (line[0] == '\n')
		return (TRUE);
	while (*line == ' ')
		line++;
	i = 0;
	while (i < 6)
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
	t_list	*lst;
	t_list	*prev;

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

// debugging func
static void	print_lst(t_list *lst)
{
	printf("-------------------------\n");
	while (lst)
	{
		printf("%s", (char *)(lst->content));
		lst = lst->next;
	}
	printf("\n");
}

void	parse(char *filename, t_param *param)
{
	int		errno;
	t_list	*lst;
	t_list	*map_lst;

	lst = read_file(filename, param);
	map_lst = divide_lst(&lst);
	print_lst(lst);
	print_lst(map_lst);
	errno = parse_info(lst, param);
	if (errno)
	{
		ft_lstclear(&lst, free);
		ft_lstclear(&map_lst, free);
		if (errno == ERROR)
			ft_error_exit("element: The input format is invalid", param);
		else
			ft_perror_exit("param_info", param);
	}
	ft_lstclear(&lst, free);
	parse_map(map_lst, param);
}

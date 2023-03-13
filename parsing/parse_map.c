/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/13 18:48:38 by jeongmin         ###   ########.fr       */
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
		param->map.height++;
		param->map.width = ft_max(param->map.width, ft_strlen(line));
	}
	ft_close(fd, param);
	return (lst);
}

static void	allocate_map(t_param *param, t_list *lst)
{
	int			i;
	const int	w = param->map.width;
	const int	h = param->map.height;

	param->map.arr = (char **)malloc(sizeof(char *) * (h + 1));
	if (!param->map.arr)
	{
		ft_lstclear(&lst, free);
		ft_perror_exit("init_map", param);
	}
	i = 0;
	while (i < h)
	{
		param->map.arr[i] = (char *)malloc(sizeof(char) * (w + 1));
		if (!param->map.arr[i])
		{
			ft_lstclear(&lst, free);
			ft_perror_exit("init_map", param);
		}
		i++;
	}
	param->map.arr[i] = NULL;
}

static void	cast_map(t_param *param, t_list *lst)
{
	int		i;
	int		j;
	char	*line;
	char	**arr;

	i = 0;
	arr = param->map.arr;
	while (i < param->map.height)
	{
		j = 0;
		line = (char *)(lst->content);
		while (line[j] && line[j] != '\n')
		{
			arr[i][j] = line[j];
			j++;
		}
		while (j < param->map.width)
		{
			arr[i][j] = ' ';
			j++;
		}
		arr[i][j] = 0;
		i++;
		lst = lst->next;
	}
}

// debugging func
// static void	print_lst(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s", (char *)(lst->content));
// 		lst = lst->next;
// 	}
// }

// debugging func
// static void	print_arr(char **map)
// {
// 	int	i;

// 	i = 0;
// 	printf("-------------------\n");
// 	printf("[map]\n");
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}
// }

char	**parse_map(char *filename, t_param *param)
{
	char	**arr;
	t_list	*lst;

	arr = NULL;
	lst = read_map(filename, param);
	allocate_map(param, lst);
	cast_map(param, lst);
	check_map(param, lst);
	cast_map(param, lst);
	ft_lstclear(&lst, free);
	return (arr);
}

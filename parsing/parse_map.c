/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/16 20:26:31 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

static void	get_dimensions(t_map *map, t_list *lst)
{
	char	*line;

	while (lst)
	{
		line = lst->content;
		map->height++;
		map->width = ft_max(map->width, ft_strlen(line));
		lst = lst->next;
	}
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

void	parse_map(t_list *lst, t_param *param)
{
	if (lst == NULL)
		ft_error_exit("map: No map information available.", param);
	get_dimensions(&(param->map), lst);
	allocate_map(param, lst);
	cast_map(param, lst);
	check_map(param, lst);
	cast_map(param, lst);
	ft_lstclear(&lst, free);
}

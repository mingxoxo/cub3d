/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/12 20:02:12 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_path(int n[2], int h, int w, char **arr)
{
	if (0 <= n[X] && n[X] < h && 0 <= n[Y] && n[Y] < w)
	{
		if (arr[n[X]][n[Y]] == '1' || arr[n[X]][n[Y]] == '_')
			return (1);
		if (n[X] == 0 || n[X] == h - 1 || n[Y] == 0 || n[Y] == w - 1)
			return (-1);
		if (arr[n[X]][n[Y]] == ' ')
			return (-1);
		return (0);
	}
	return (-1);
}

static int	bfs(t_node *queue, int h, int w, char **arr)
{
	int			i;
	int			n[2];
	int			cor[2];
	const int	d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};

	while (queue->next)
	{
		dequeue(queue, cor);
		arr[cor[X]][cor[Y]] = '_';
		i = 0;
		while (i < 4)
		{
			n[X] = cor[X] + d[X][i];
			n[Y] = cor[Y] + d[Y][i];
			i++;
			if (is_path(n, h, w, arr) == -1)
				return (-1);
			if (is_path(n, h, w, arr))
				continue ;
			arr[n[X]][n[Y]] = '_';
			if (enqueue(queue, n[X], n[Y]))
				return (1);
		}
	}
	return (0);
}	

static int	check_path(t_map *map, char **arr)
{
	int		i;
	int		j;
	int		errno;
	t_node	*queue;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("NSEW0", arr[i][j]))
			{
				if (init_queue(&queue, i, j))
					return (1);
				errno = bfs(queue, map->height, map->width, map->arr);
				ft_free_queue(&queue);
				if (errno)
					return (errno);
			}
			j++;
		}
		i++;
	}
	return (errno);
}

static char	*check_char(t_info *info, char **arr)
{
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_strchr("NSEW", arr[i][j]))
			{
				if (info->sx != -1 || info->sy != -1)
					return ("map: There must be one player.");
				info->sx = i;
				info->sy = j;
			}
			else if (ft_strchr("01 ", arr[i][j]) == NULL)
				return ("map: The character must be \
0, 1, N, S, E, W or space.");
			j++;
		}
		i++;
	}
	if (info->sx == -1 && info->sy == -1)
		return ("map: There must be one player.");
	return (0);
}

void	check_map(t_param *param, t_list *lst)
{
	int		errno;
	char	*error_msg;

	error_msg = check_char(&(param->info), param->map.arr);
	if (error_msg)
	{
		ft_lstclear(&lst, free);
		ft_error_exit(error_msg, param);
	}
	errno = check_path(&(param->map), param->map.arr);
	if (errno)
	{
		ft_lstclear(&lst, free);
		error_msg = "map: The map must be closed/surrounded by walls.";
		if (errno == -1)
			ft_error_exit(error_msg, param);
		ft_perror_exit("check_path", param);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:13:33 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/09 18:24:27 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_path(int n[2], int h, int w, char **arr)
{
	if (0 < n[X] && n[X] < h && 0 < n[Y] && n[Y] < w)
	{
		if (arr[n[X]][n[Y]] == '1' || visited[n[X]][n[Y]] == 'O')
			return (ERROR);
		visited[n[X]][n[Y]] = 'O';
		if (arr[n[X]][n[Y]] == 'C')
			chk->item--;
		else if (arr[n[X]][n[Y]] == 'E')
			chk->exit--;
		return (SUCCESS);
	}
	return (ERROR);
}

static int	bfs(t_node *queue, char **arr, int sx, int sy)
{
	int			i;
	int			n[2];
	int			cor[2];
	const int	d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};

	if (init_queue(&queue, sx, sy))
		return (1);
	while (queue->next)
	{
		dequeue(queue, cor);
		i = 0;
		while (i < 4)
		{
			n[X] = cor[X] + d[X][i];
			n[Y] = cor[Y] + d[Y][i];
			i++;
			if (is_path(chk, n, visited, arr) == ERROR)
				continue ;
			if (enqueue(queue, n[X], n[Y]))
				return (1);
		}
	}
	ft_free_queue(&queue);
	return (0);
}	

static int	check_path(t_info *info, char **arr)
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
				arr[i][j] = '_';
				errno = bfs(queue, map->arr, i, j);
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
				return ("map: The character must be  \
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
	char	*error_msg;

	error_msg = check_char(&(param->info), param->map.arr);
	if (error_msg)
	{
		ft_lstclear(&lst, free);
		ft_error_exit(error_msg, param);
	}
}

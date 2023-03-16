/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:53:42 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/16 17:17:04 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_texture(t_info *info, char **split)
{
	char	**path;

	path = NULL;
	if (ft_strcmp(split[0], "NO") == 0)
		path = &(info->no.path);
	else if (ft_strcmp(split[0], "SO") == 0)
		path = &(info->so.path);
	else if (ft_strcmp(split[0], "WE") == 0)
		path = &(info->we.path);
	else if (ft_strcmp(split[0], "EA") == 0)
		path = &(info->ea.path);
	else
		return (ERROR);
	if (*path)
		return (ERROR);
	*path = ft_strdup(split[1]);
	if (!(*path))
		return (ALLOC_FAILED);
	return (SUCCESS);
}

static int	parse_color(t_info *info, char **split)
{
	char	**path;

	path = NULL;
	if (ft_strcmp(split[0], "F") == 0)
		path = &(info->f.info);
	else if (ft_strcmp(split[0], "C") == 0)
		path = &(info->c.info);
	if (*path)
		return (ERROR);
	*path = ft_strdup(split[1]);
	if (!(*path))
		return (ALLOC_FAILED);
	return (SUCCESS);
}

static int	print_info(t_info *info)
{
	printf("-------------------\n");
	printf("[info]\n");
	printf("NO: [%s]\n", info->no.path);
	printf("SO: [%s]\n", info->so.path);
	printf("WE: [%s]\n", info->we.path);
	printf("EA: [%s]\n", info->ea.path);
	printf("F: [%s]\n", info->f.info);
	printf("C: [%s]\n", info->c.info);
	if (!info->no.path || !info->so.path || !info->we.path || !info->ea.path)
		return (ERROR);
	if (!info->f.info || !info->c.info)
		return (ERROR);
	return (SUCCESS);
}

// debugging func
static void	print_split(char **split)
{
	int	i;

	i = 0;
	printf("-------------------\n");
	printf("[split]\n");
	while (split[i])
	{
		printf("(%s)\n", split[i]);
		i++;
	}
}

int	parse_info(t_list *lst, t_param *param)
{
	char	*line;
	char	**split;
	int		errno;

	errno = SUCCESS;
	while (lst)
	{
		line = (char *)(lst->content);
		lst = lst->next;
		if (line[0] == '\n')
			continue ;
		*(ft_strchr(line, '\n')) = 0;
		split = ft_split(line, ' ');
		print_split(split);
		if (!split[0] || !split[1] || split[2])
		{
			ft_free_two_array(&split);
			return (ERROR);
		}
		if (split[0][0] == 'F' || split[0][0] == 'C')
			errno = parse_color(&param->info, split);
		else
			errno = parse_texture(&param->info, split);
		ft_free_two_array(&split);
		if (errno)
			return (errno);
	}
	if (print_info(&param->info))
		return (ERROR);
	return (SUCCESS);
}

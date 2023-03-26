/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:53:42 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/25 23:59:38 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_detail(t_info *info, char **tokens)
{
	char	**path;

	path = NULL;
	if (ft_strcmp(tokens[0], "NO") == 0)
		path = &(info->no.path);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		path = &(info->so.path);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		path = &(info->we.path);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		path = &(info->ea.path);
	else if (ft_strcmp(tokens[0], "F") == 0)
		path = &(info->f.info);
	else if (ft_strcmp(tokens[0], "C") == 0)
		path = &(info->c.info);
	else
		return (ERROR);
	if (*path)
		return (ERROR);
	*path = ft_strdup(tokens[1]);
	if (!(*path))
		return (ALLOC_FAILED);
	return (SUCCESS);
}

static int	check_all_info_exists(t_info *info)
{
	if (!info->no.path || !info->so.path || !info->we.path || !info->ea.path)
		return (ERROR);
	if (!info->f.info || !info->c.info)
		return (ERROR);
	return (SUCCESS);
}

static int	split_line(char *line, char ***tokens)
{
	size_t	len;
	char	**split;

	*tokens = ft_split(line, ' ');
	split = *tokens;
	if (!split)
		return (ALLOC_FAILED);
	if (!split[0] || !split[1] || (split[2] && ft_strcmp(split[2], "\n")))
	{
		ft_free_two_array(tokens);
		return (ERROR);
	}
	len = ft_strlen(split[1]);
	if (len && split[1][len - 1] == '\n')
		split[1][len - 1] = 0;
	return (SUCCESS);
}

int	parse_info(t_list *lst, t_param *param)
{
	char	*line;
	char	**tokens;
	int		errno;

	errno = SUCCESS;
	while (lst)
	{
		line = (char *)(lst->content);
		lst = lst->next;
		if (line[0] == '\n')
			continue ;
		errno = split_line(line, &tokens);
		if (errno)
			return (errno);
		errno = parse_detail(&param->info, tokens);
		ft_free_two_array(&tokens);
		if (errno)
			return (errno);
	}
	if (check_all_info_exists(&param->info))
		return (ERROR);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:59:52 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 23:57:08 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	parse_detail(t_img *img, char **tokens)
{
	img->path = ft_strdup(tokens[1]);
	if (!(img->path))
		return (ALLOC_FAILED);
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

static int	init_img_arr(t_list *lst, t_img **img, int *cnt)
{
	int	i = 0;
	while (lst)
	{
		(*cnt)++;
		lst = lst->next;
	}
	if (*cnt == 0)
		return (SUCCESS);
	*img = (t_img *)malloc(sizeof(t_img) * (*cnt));
	if (!(*img))
		return (ALLOC_FAILED);
	while (i < *cnt)
	{
		init_img((*img) + i);
		i++;
	}
	return (SUCCESS);
}

//디버깅
static void print_img_arr(t_img *img, int cnt)
{
	int		i;

	i = 0;
	while (i < cnt)
	{
		printf("%i, [%s]\n", i, img[i].path);
		i++;
	}
}

int	parse_info_bonus(t_list *lst, t_img **img, int *cnt)
{
	char	**tokens;
	int		i;
	int		errno;

	if (init_img_arr(lst, img, cnt))
		return (ALLOC_FAILED);
	i = 0;
	errno = SUCCESS;
	while (lst)
	{
		errno = split_line(lst->content, &tokens);
		if (errno)
			return (errno);
		errno = parse_detail(*img + i, tokens);
		ft_free_two_array(&tokens);
		if (errno)
			return (errno);
		lst = lst->next;
		i++;
	}
	print_img_arr(*img, *cnt);
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:09:04 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:30:56 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_split_strs(const char *str, char c)
{
	int		first;
	size_t	cnt;

	first = 1;
	cnt = 0;
	while (*str)
	{
		if (*str == c)
			first = 1;
		else if (first == 1)
		{
			cnt++;
			first = 0;
		}
		str++;
	}
	return (cnt);
}

static void	free_two_array(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = 0;
}

static char	**split_array(char **dst, char *str, char c, size_t cnt)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < cnt)
	{
		while (*str == c)
			str++;
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		dst[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (dst[i] == 0)
		{
			free_two_array(&dst);
			return (NULL);
		}
		ft_strlcpy(dst[i], str, len + 1);
		str += len + 1;
		i++;
	}
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	size_t	cnt;
	char	**dst;

	cnt = count_split_strs(s, c);
	dst = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!dst || !split_array(dst, (char *)s, c, cnt))
		return (NULL);
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:02:06 by jeongmin          #+#    #+#             */
/*   Updated: 2022/08/06 19:03:10 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strchr_idx(char *s, char c, ssize_t *idx)
{
	ssize_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
		{
			*idx += i + 1;
			return (GSUCCESS);
		}
		i++;
	}
	*idx += i;
	return (GFAIL);
}

static char	*ft_strjoin_size(char *s1, char *s2, ssize_t cpy_size)
{
	char	*dst;
	ssize_t	len;
	ssize_t	idx;

	len = cpy_size;
	ft_strchr_idx(s1, '\0', &len);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	idx = 0;
	while (s1 && *s1 && idx < len)
	{
		dst[idx] = *s1;
		s1++;
		idx++;
	}
	while (s2 && *s2 && idx < len)
	{
		dst[idx] = *s2;
		s2++;
		idx++;
	}
	dst[idx] = 0;
	return (dst);
}

ssize_t	ft_remake_cache(char **cache, char *buf, ssize_t size)
{
	char	*tmp;

	buf[size] = '\0';
	tmp = ft_strjoin_size(*cache, buf, size);
	if (!tmp)
		return (GFAIL);
	if (*cache)
		free(*cache);
	*cache = tmp;
	return (GSUCCESS);
}

ssize_t	ft_make_line(char **cache, char **line, ssize_t idx)
{
	char	*tmp;

	if (*cache && idx)
	{
		*line = ft_strjoin_size(NULL, *cache, idx);
		if (!(*line))
			return (GFAIL);
	}
	if (*cache && (*cache)[idx])
	{
		tmp = ft_strjoin_size(*cache + idx, NULL, 0);
		if (!tmp)
			return (GFAIL);
	}
	else
		tmp = 0;
	if (*cache)
		free(*cache);
	*cache = tmp;
	return (GSUCCESS);
}

ssize_t	ft_read_file(char **cache, int fd, ssize_t *idx)
{
	char	*buf;
	ssize_t	size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (GFAIL);
	while (1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			break ;
		if (ft_remake_cache(cache, buf, size) == GFAIL)
		{
			free(buf);
			return (GFAIL);
		}
		if (ft_strchr_idx(buf, '\n', idx) != GFAIL)
			break ;
	}
	free(buf);
	if (size < 0)
		*idx = READ_FAIL;
	return (GSUCCESS);
}

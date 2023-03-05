/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:55:42 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:24:53 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	s_len;
	char	*dst;

	s_len = ft_strlen(s);
	if (s_len <= start)
		size = 0;
	else if (start + len <= s_len)
		size = len;
	else
		size = s_len - start + 1;
	dst = (char *)ft_calloc(size + 1, sizeof(char));
	if (!dst)
		return (dst);
	if (size == 0)
		return (dst);
	ft_strlcpy(dst, s + start, size + 1);
	return (dst);
}

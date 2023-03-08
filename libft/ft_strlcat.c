/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:06:43 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:07:13 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	idx = dst_len;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (idx < dstsize - 1 && *src != '\0')
	{
		dst[idx] = *src;
		src++;
		idx++;
	}
	dst[idx] = '\0';
	return (dst_len + src_len);
}

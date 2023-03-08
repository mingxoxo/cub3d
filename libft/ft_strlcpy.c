/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:06:32 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:06:34 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	len;

	idx = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (idx < dstsize - 1 && idx < len)
	{
		dst[idx] = src[idx];
		idx++;
	}
	dst[idx] = '\0';
	return (len);
}

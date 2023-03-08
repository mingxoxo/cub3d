/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:02:57 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:05:21 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;
	size_t			i;

	i = 0;
	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (uc_dst < uc_src)
	{
		while (i < len)
		{
			uc_dst[i] = uc_src[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			uc_dst[len] = uc_src[len];
	}
	return (dst);
}

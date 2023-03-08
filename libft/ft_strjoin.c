/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:45:02 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:26:01 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)ft_calloc(len, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcat(dst, s1, len);
	ft_strlcat(dst, s2, len);
	return (dst);
}

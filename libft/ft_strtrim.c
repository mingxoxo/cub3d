/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:26:44 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:27:46 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = ft_strlen(s1);
	if (j == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i] == '\0')
		return ((char *)ft_calloc(1, sizeof(char)));
	while (s1[j - 1] && ft_strchr(set, s1[j - 1]))
		j--;
	dst = (char *)ft_calloc(j - i + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1 + i, j - i + 1);
	return (dst);
}

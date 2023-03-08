/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:10:12 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:10:50 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = 0;
	while (1)
	{
		if ((char)c == *s)
			result = (char *)s;
		if (*s == 0)
			break ;
		s++;
	}	
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:32:58 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:31:49 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size(long long nbr)
{
	if (nbr / 10 == 0)
		return (1);
	return (count_size(nbr / 10) + 1);
}

static void	fill_array(char *dst, long long ln, size_t size)
{
	size_t	i;

	i = 0;
	if (ln < 0)
	{
		dst[i] = '-';
		i++;
		ln *= -1;
	}
	while (size > i)
	{
		dst[size - 1] = ln % 10 + '0';
		size--;
		ln /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t		size;
	long long	ln;
	char		*dst;

	size = 0;
	ln = (long long)n;
	if (ln < 0)
		size = 1;
	size = size + count_size(ln);
	dst = (char *)ft_calloc(size + 1, sizeof(char));
	if (!dst)
		return (NULL);
	fill_array(dst, ln, size);
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:26:16 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:56:28 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static unsigned char	*check_starting_point(unsigned char *str, int *sign)
{
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		str++;
		*sign = -1;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;
	unsigned char		*uc_str;

	result = 0;
	sign = 1;
	uc_str = check_starting_point((unsigned char *)str, &sign);
	while (*uc_str && ft_isdigit(*uc_str))
	{
		result = result * 10 + (*uc_str - '0');
		if (sign == 1 && result >= LLONG_MAX)
			return (-1);
		else if (sign == -1 && result && result - 1 >= LLONG_MAX)
			return (0);
		uc_str++;
	}
	return (sign * result);
}

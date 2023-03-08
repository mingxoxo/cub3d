/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:59:54 by jeongmin          #+#    #+#             */
/*   Updated: 2022/07/20 15:46:34 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_recursion(int nb, int fd)
{
	if (nb < 10)
	{
		ft_putchar(nb + '0', fd);
	}
	else
	{
		ft_putnbr_recursion(nb / 10, fd);
		ft_putchar(nb % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ft_putchar('-', fd);
			n *= -1;
		}
		ft_putnbr_recursion(n, fd);
	}
}

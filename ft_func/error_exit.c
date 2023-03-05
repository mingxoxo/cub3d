/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/05 19:00:10 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

void	ft_perror_exit(const char *s, t_param *param)
{
	write(2, "Error\n", 6);
	perror(s);
	ft_free_param(param);
	exit(1);
}

void	ft_error_exit(const char *s, t_param *param)
{
	if (write(2, "Error\n", 6) == -1)
		ft_perror_exit("write error", param);
	if (write(2, s, ft_strlen(s)) == -1)
		ft_perror_exit("write error", param);
	if (write(2, "\n", 1) == -1)
		ft_perror_exit("write error", param);
	ft_free_param(param);
	exit(1);
}

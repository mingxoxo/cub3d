/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/04/04 17:55:24 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cub3d_bonus.h"

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
	if (s)
	{
		if (write(2, s, ft_strlen(s)) == -1)
			ft_perror_exit("write error", param);
		if (write(2, "\n", 1) == -1)
			ft_perror_exit("write error", param);
	}
	ft_free_param(param);
	exit(1);
}

void	ft_img_error_exit(const char *path, t_param *param)
{
	const char	*msg = "Sorry. The program can only use \
.xpm files with the correct path as image files.\n";

	if (write(2, "Error\nmlx: img load error: ", 27) == -1)
		ft_perror_exit("write error", param);
	if (path)
	{
		if (write(2, path, ft_strlen(path)) == -1)
			ft_perror_exit("write error", param);
		if (write(2, "\n", 1) == -1)
			ft_perror_exit("write error", param);
	}
	if (write(2, msg, ft_strlen(msg)) == -1)
		ft_perror_exit("write error", param);
	ft_free_param(param);
	exit(1);
}

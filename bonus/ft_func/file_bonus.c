/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 15:11:51 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d_bonus.h"

int	ft_open(const char *path, t_param *param)
{
	int	file_fd;

	file_fd = open(path, O_RDONLY, 0755);
	if (file_fd < 1)
		ft_perror_exit(NULL, param);
	return (file_fd);
}

void	ft_close(int fd, t_param *param)
{
	if (close(fd))
		ft_perror_exit(NULL, param);
}

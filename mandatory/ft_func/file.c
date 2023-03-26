/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:32:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/05 18:54:35 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

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

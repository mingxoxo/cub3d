/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:35:05 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/14 18:44:11 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_arg(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		ft_error_exit("Arguments: A map in format *.cub", NULL);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + (len - 4), ".cub") != 0)
		ft_error_exit("Arguments: A map in format *.cub", NULL);
}

int	main(int argc, char **argv)
{
	t_param	param;

	check_arg(argc, argv);
	init_param(&param);
	parse(argv[1], &param);
	ft_free_param(&param);
	return (0);
}

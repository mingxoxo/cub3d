/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:35:05 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/19 20:30:27 by wonyang          ###   ########seoul.kr  */
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

int	exit_game(t_param *param)
{
	ft_free_param(param);
	exit(0);
}

static void	put_images(t_param *param)
{
	mlx_put_image_to_window(param->mlx, param->win, \
			param->info.ea.ptr, 0, 0);
	mlx_put_image_to_window(param->mlx, param->win, \
			param->info.we.ptr, 400, 0);
	mlx_put_image_to_window(param->mlx, param->win, \
			param->info.so.ptr, 800, 0);
	mlx_put_image_to_window(param->mlx, param->win, \
			param->info.no.ptr, 1200, 0);
}

int	main(int argc, char **argv)
{
	t_param	param;

	check_arg(argc, argv);
	init_param(&param);
	parse(argv[1], &param);
	init_ray(&param);
	put_images(&param);
	mlx_hook(param.win, 2, 0, key_press, &param);
	mlx_hook(param.win, 17, 0, exit_game, &param);
	mlx_loop(param.mlx);
	return (0);
}

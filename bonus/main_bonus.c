/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:35:05 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 17:49:16 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	init_ray(&param);
	render_screen(&param);
	mlx_key_hook(param.mlx.win, key_release, &param);
	mlx_hook(param.mlx.win, 2, 0, key_press, &param);
	mlx_hook(param.mlx.win, 6, 0, mouse_move, &param);
	mlx_hook(param.mlx.win, 17, 0, exit_game, &param);
	mlx_loop_hook(param.mlx.mlx, loop, &param);
	mlx_loop(param.mlx.mlx);
	return (0);
}

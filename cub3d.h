/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:33:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/07 01:19:12 by jeongmin         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}			t_img;

typedef struct s_info
{
	int	sx;
	int	sy;
}		t_info;

typedef struct s_map
{
	int		height;
	int		width;
	char	**arr;
}			t_map;

typedef struct s_param
{
	t_map	map;
	t_info	info;
}	t_param;

//parsing
char	**parse_map(char *filename, t_param *param);

// ft_func
int		ft_open(const char *path, t_param *param);
void	ft_close(int fd, t_param *param);
void	ft_perror_exit(const char *s, t_param *param);
void	ft_error_exit(const char *s, t_param *param);
void	*ft_malloc(size_t size, t_param *param);
char	**ft_free_two_array(char ***str);
void	ft_free_param(t_param *param);
t_list	*ft_lstnew_cub(void *str, t_list *lst, t_param *param);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
#endif

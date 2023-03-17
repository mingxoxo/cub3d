/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:33:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/17 16:03:32 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"

# define X 0
# define Y 1

# define TRUE 1
# define FALSE 0

# define ERROR -1
# define SUCCESS 0
# define ALLOC_FAILED 1

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_img
{
	char	*path;
	void	*ptr;
	int		w;
	int		h;
}			t_img;

typedef struct s_color
{
	char	*info;
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_info
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_color	f;
	t_color	c;
}		t_info;

typedef struct s_map
{
	int		sx;
	int		sy;
	int		height;
	int		width;
	char	**arr;
}			t_map;

typedef struct s_param
{
	t_map	map;
	t_info	info;
}	t_param;

// init
void	init_param(t_param *param);

// parsing
void	parse(char *filename, t_param *param);
int		parse_info(t_list *lst, t_param *param);
void	parse_map(t_list *lst, t_param *param);
int		parse_color(t_info *info);
void	check_map(t_param *param, t_list *lst);

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

// ds_queue.c
t_node	*init_node(int x, int y);
int		init_queue(t_node **queue, int sx, int sy);
void	ft_free_queue(t_node **queue);
int		enqueue(t_node *head, int x, int y);
void	dequeue(t_node *head, int cor[2]);

#endif

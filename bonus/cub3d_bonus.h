/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:33:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/04/04 17:55:38 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include "../mlx_opengl/mlx.h"

# define X 0
# define Y 1

# define TRUE 1
# define FALSE 0

# define ERROR -1
# define SUCCESS 0
# define ALLOC_FAILED 1

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define MINI_W 25
# define MINI_H 25

enum	e_keycode
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_SPACE = 49
};

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_img
{
	void	*ptr;
	char	*path;
	char	*data;
	int		w;
	int		h;
	int		bpp;
	int		lsize;
	int		end;
}			t_img;

typedef struct s_color
{
	char	*info;
	int		rgb[3];
}			t_color;

typedef struct s_coor
{
	double	x;
	double	y;
	double	s_dst;
}			t_coor;

typedef struct s_spr
{
	t_coor	*arr;
	int		sp_cnt;
}			t_spr;

typedef struct s_info
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	*d;
	t_img	*sp;
	t_color	f;
	t_color	c;
	int		d_cnt;
	int		sp_cnt;
}		t_info;

typedef struct s_map
{
	int		sx;
	int		sy;
	char	sdir;
	int		height;
	int		width;
	char	**arr;
}			t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bit;
	int		lsize;
	int		end;
	char	*ptr;
}			t_mlx;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_ray;

typedef struct s_dda
{
	double	ray_dir[2];
	int		map[2];
	double	side_dst[2];
	double	delta_dst[2];
	int		step[2];
	double	w_dst;
	int		side;
	int		l_height;
	int		draw[2];
	t_img	img;
	int		tex[2];
}			t_dda;

typedef struct s_spc
{
	double	tf[2];
	int		s_scn;
	int		m_scn;
	int		s_height;
	int		s_width;
	int		d_start[2];
	int		d_end[2];
	int		tex[2];
	t_img	img;
}			t_spc;

typedef struct s_param
{
	t_mlx	mlx;
	t_map	map;
	t_info	info;
	t_ray	ray;
	t_spr	spr;
	int		key[256];
	int		mouse[2];
	int		frame;
}			t_param;

// event.c
int		exit_game(t_param *param);
int		key_release(int key, t_param *param);
int		key_press(int key, t_param *param);
int		mouse_move(int x, int y, t_param *param);

// init
void	init_param(t_param *param);
void	init_img(t_img *img);

// key_press.c
int		loop(t_param *param);

// minimap
void	draw_minimap(t_param *param);

// parsing
void	parse(char *filename, t_param *param);
int		parse_info(t_list *lst, t_param *param);
void	parse_map(t_list *lst, t_param *param);
int		parse_color(t_info *info);
void	check_map(t_param *param, t_list *lst);
void	get_image(t_param *param);
void	divide_lst_by_type(t_list **m_lst, t_list **d_lst, t_list **sp_lst);
int		parse_info_bonus(t_list *lst, t_img **img, int *cnt);
int		check_bonus(t_list *map_lst, t_list *d_lst, t_list *sp_lst);

// render
int		can_move(int x, int y, char **map);
void	render_sprite(t_param *param, double buf[WIN_WIDTH]);
void	sort_sprite(t_param	*param);
void	init_sprite(t_param *param);
void	init_ray(t_param *param);
void	print_dot(t_mlx mlx, int x, int y, int color);
void	print_mini_rect(t_mlx mlx, int x, int y, int color);
void	draw_line(t_param *param, t_dda *d, int x);
void	fill_background(t_mlx mlx, int c1[3], int c2[3]);
void	render_screen(t_param *param);

// ft_func
int		ft_open(const char *path, t_param *param);
void	ft_close(int fd, t_param *param);
void	ft_perror_exit(const char *s, t_param *param);
void	ft_error_exit(const char *s, t_param *param);
void	ft_img_error_exit(const char *path, t_param *param);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:20:59 by jeongmin          #+#    #+#             */
/*   Updated: 2022/12/17 19:55:41 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define READ_FAIL -2
# define GFAIL -1
# define GSUCCESS 0

# include <stdlib.h>
# include <unistd.h>

typedef struct s_chche
{
	int				fd;
	char			*cache;
	struct s_chche	*prev;
	struct s_chche	*next;
}					t_chche;

int		get_next_line(int fd, char **line);
int		ft_clear_memory(t_chche **head, char **memory);

t_chche	*ft_found_fd_node(t_chche **head, int fd);

ssize_t	ft_strchr_idx(char *s, char c, ssize_t *idx);
ssize_t	ft_read_file(char **cache, int fd, ssize_t *idx);
ssize_t	ft_remake_cache(char **cache, char *buf, ssize_t size);
ssize_t	ft_make_line(char **cache, char **line, ssize_t idx);

void	ft_delete_node(t_chche **node, t_chche **head);

#endif
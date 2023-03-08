/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:05:42 by jeongmin          #+#    #+#             */
/*   Updated: 2022/08/06 19:08:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_clear_memory(t_chche **head, char **memory)
{
	t_chche	*tmp;
	t_chche	*del_node;

	tmp = *head;
	while (tmp)
	{
		del_node = tmp;
		tmp = tmp->next;
		if (del_node->cache)
			free(del_node->cache);
		free(del_node);
	}
	*head = 0;
	if (*memory)
		free(*memory);
	*memory = 0;
	return (GFAIL);
}

t_chche	*ft_found_fd_node(t_chche **head, int fd)
{
	t_chche	*tmp;
	t_chche	*node;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	node = (t_chche *)malloc(sizeof(t_chche));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->cache = NULL;
	node->prev = tmp;
	node->next = NULL;
	if (!tmp)
		*head = node;
	else
		tmp->next = node;
	return (node);
}

void	ft_delete_node(t_chche **node, t_chche **head)
{
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	else
		*head = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->cache)
		free((*node)->cache);
	free(*node);
	*node = 0;
}

int	get_next_line(int fd, char **line)
{
	static t_chche	*head;
	t_chche			*fd_node;
	ssize_t			idx;

	if (fd == GFAIL || BUFFER_SIZE < 1)
		return (GFAIL);
	*line = 0;
	idx = 0;
	fd_node = ft_found_fd_node(&head, fd);
	if (!fd_node)
		return (ft_clear_memory(&head, line));
	if (ft_strchr_idx(fd_node->cache, '\n', &idx) == GFAIL)
	{
		if (ft_read_file(&(fd_node->cache), fd, &idx) == GFAIL)
			return (ft_clear_memory(&head, line));
	}
	if (idx != READ_FAIL && ft_make_line(&(fd_node->cache), line, idx) == GFAIL)
		return (ft_clear_memory(&head, line));
	if (idx == READ_FAIL || fd_node->cache == NULL)
		ft_delete_node(&fd_node, &head);
	return (GSUCCESS);
}

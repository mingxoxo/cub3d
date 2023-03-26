/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds_queue_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:13:46 by jeongmin          #+#    #+#             */
/*   Updated: 2023/03/26 15:11:51 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "cub3d_bonus.h"

t_node	*init_node(int x, int y)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	init_queue(t_node **queue, int sx, int sy)
{
	*queue = init_node(-1, -1);
	if (!(*queue))
		return (1);
	if (enqueue(*queue, sx, sy))
	{
		free(*queue);
		return (1);
	}
	return (0);
}

void	ft_free_queue(t_node **queue)
{
	t_node	*tmp;
	t_node	*del;

	tmp = *queue;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		free(del);
	}
	*queue = 0;
}

int	enqueue(t_node *head, int x, int y)
{
	t_node	*new;
	t_node	*last;

	new = init_node(x, y);
	if (!new)
		return (1);
	last = head;
	while (last->next)
		last = last->next;
	new->prev = last;
	last->next = new;
	return (0);
}

void	dequeue(t_node *head, int cor[2])
{
	t_node	*del;

	del = head->next;
	if (del)
	{
		head->next = del->next;
		if (del->next)
			del->next->prev = del->prev;
	}
	else
		head->next = NULL;
	cor[X] = del->x;
	cor[Y] = del->y;
	free(del);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfsearch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:35:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/03/02 19:35:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list				*ft_lstdup(t_list *lst, int level)
{
	t_list	*new;
	t_list	*n;

	if (!lst)
		return (NULL);
	new = ft_memalloc(sizeof(t_list));
	new->content_size = (size_t)level;
	new->content = lst->content;
	n = new;
	lst = lst->next;
	while (lst)
	{
		if (lst->content_size == 1)
			continue ;
		n->next = ft_memalloc(sizeof(t_list));
		n->next->content_size = level;
		n->next->content = lst->content;
		n = n->next;
		n->next = NULL;
		lst = lst->next;
	}
	return (new);
}

t_list				*ft_enqueue(t_list *queue, t_list *link, int level)
{
	t_list	*q;

	q = queue;
	if (q)
	{
		while (q->next)
			q = q->next;
		q->next = ft_lstdup(link, level);
	}
	else
		queue = ft_lstdup(link, level);
	return (queue);
}

t_list				*ft_dequeue(t_list *queue)
{
	t_list	*q;

	if (!queue)
		return (NULL);
	q = queue->next;
	ft_memdel((void **)&queue);
	return (q);
}

static t_list		*ft_addpath(t_list *path, t_vertex *vertex)
{
	t_list	*node;

	if (!vertex)
		return (path);
	node = ft_memalloc(sizeof(t_list));
	if (!node)
		return (path);
	node->content = vertex;
	node->next = path;
	path = node;
	return (path);
}

t_list				*ft_bfs(t_graph *graph)
{
	t_list		*queue;
	t_list		*path;
	t_vertex	*tmp;

	if (!graph)
		return (NULL);
	graph->start->status = 1;
	queue = ft_enqueue(NULL, graph->start->link, graph->start->status + 1);
	path = ft_addpath(NULL, graph->start);
	while (queue)
	{
		tmp = queue->content;
		if (tmp->status == 0)
		{
			tmp->status = (int)queue->content_size;
			path = ft_addpath(path, (t_vertex *)queue->content);
			queue = ft_enqueue(queue, tmp->link, tmp->status + 1);
		}
		queue = ft_dequeue(queue);
		ft_queueshow(path);
		ft_printf("\n");
	}
	return (path);
}

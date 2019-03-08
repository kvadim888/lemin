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

t_list				*ft_linkdup(t_list *lst, t_vertex *vertex, int level)
{
	t_list	*new;
	t_list	*tmp;

	tmp = NULL;
	new = NULL;
	while (lst)
	{
		if (lst->content_size < 1)
		{
			new = ft_memalloc(sizeof(t_list));
			new->content_size = level;
			new->content = ft_memalloc(sizeof(t_path));
			((t_path *)new->content)->curr = lst->content;
			((t_path *)new->content)->root = vertex;
			new->next = tmp;
			tmp = new;
		}
		lst = lst->next;
	}
	return (new);
}

t_list				*ft_enqueue(t_list *queue, t_vertex *vertex)
{
	t_list	*q;

	q = queue;
	if (q)
	{
		while (q->next)
			q = q->next;
		q->next = ft_linkdup(vertex->link, vertex, vertex->status + 1);
	}
	else
		queue = ft_linkdup(vertex->link, vertex, vertex->status + 1);
	return (queue);
}

t_list				*ft_dequeue(t_list *queue)
{
	t_list	*q;

	if (!queue)
		return (NULL);
	q = queue->next;
	ft_memdel(&(queue->content));
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
	t_path		*tmp;
	t_vertex	*vertex;

	if (!graph)
		return (0);
	queue = ft_enqueue(NULL, graph->start);
	graph->start->root = NULL;
	tmp = queue->content;
	path = NULL;
	while (queue && tmp->curr != graph->end)
	{
		tmp = queue->content;
		if (tmp->curr->status == 0)
		{
			tmp->curr->root = tmp->root;
			tmp->curr->status = (int)queue->content_size;
			queue = ft_enqueue(queue, tmp->curr);
		}
		queue = ft_dequeue(queue);
	}
	while (queue)
		queue = ft_dequeue(queue);
	vertex = graph->end;
	while (vertex)
	{
		path = ft_addpath(path, vertex);
		if (vertex == graph->start)
			break;
		vertex = vertex->root;
	}
	return (path);
}

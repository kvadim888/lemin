/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:32:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list		*ft_enqueue(t_list *queue, t_list *link, int level)
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

t_list		*ft_dequeue(t_list *queue)
{
	t_list	*q;

	if (!queue)
		return (NULL);
	q = queue->next;
	ft_memdel((void **)&queue);
	return (q);
}

t_list		*ft_addpath(t_list *path, t_vertex *vertex)
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

t_list		*ft_cutlink(t_list *prev, t_list *link, t_vertex *vertex)
{
	if (prev)
		prev->next = link->next;
	else
		vertex->link = link->next;
	ft_memdel((void **)&link);
	link = (prev) ? prev->next : vertex->link;
	return (link);
}

void		ft_linkreduce(t_graph *graph)
{
	t_list		*link;
	t_list		*prev;
	t_vertex	*tmp;

	tmp = graph->head;
	while (tmp)
	{
		prev = NULL;
		link = tmp->link;
		while (link)
		{
			if ((((t_vertex*)link->content)->status < tmp->status)
				&& (link->content != graph->end))
			{
				link = ft_cutlink(prev, link, tmp);
				continue ;
			}
			prev = link;
			link = link->next;
		}
		tmp = tmp->next;
	}
}

t_list		*ft_bfs(t_graph *graph)
{
	t_list		*queue;
	t_list		*path;
	t_vertex	*tmp;
	int			level;

	if (!graph)
		return (NULL);
	level = 1;
	graph->start->status = level;
	queue = ft_enqueue(NULL, graph->start->link, level + 1);
	path = ft_addpath(NULL, graph->start);
	while (queue)
	{
		tmp = (t_vertex *)queue->content;
		if (tmp->status == 0)
		{
			tmp->status = (int)queue->content_size;
			level = tmp->status;
			path = ft_addpath(path, (t_vertex *)queue->content);
			queue = ft_enqueue(queue, tmp->link, tmp->status + 1);
		}
		queue = ft_dequeue(queue);
	}
	graph->end->status = level + 1;
	return (path);
}

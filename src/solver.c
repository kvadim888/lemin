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

t_list		*ft_nodedup(t_list *node)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->content_size = node->content_size;
	new->content = node->content;
	new->next = NULL;
	return (new);
}

t_list		*ft_lstdup(t_list *lst, int level)
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
		n->next = ft_memalloc(sizeof(t_list));
		n->next->content_size = (size_t)level;
		n->next->content = lst->content;
		n = n->next;
		n->next = NULL;
		lst = lst->next;
	}
	return (new);
}

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
			if (((t_vertex*)link->content)->status < tmp->status)
			{
				if (prev)
					prev->next = link->next;
				else
					tmp->link = link->next;
				ft_memdel((void **)&link);
				link = (prev) ? prev->next : tmp->link;
				continue ;
			}
			prev = link;
			link = link->next;
		}
		tmp = tmp->next;
	}
}

/**
 * @brief search posible path
 * @param graph
 * @return path list with min length
 */

int		ft_islinked(t_list *path, t_vertex *vertex)
{
	t_list	*p;

	if (!path || !vertex)
		return (0);
	p = path;
	while (p)
	{
		if (p->content == vertex)
			return (1);
		p = p->next;
	}
	return (0);
}

t_list	*ft_pathsplit(t_list *path)
{
	t_vertex	*vertex;
	t_list		*list;
	t_list		*link;
	t_list		*lst;
	t_list		*tmp;

	list = ft_memalloc(sizeof(t_list));			//list of paths
	list->content = ft_nodedup(path);			//copy end vertex to path
	path = ft_dequeue(path);
	lst = list;
	tmp = lst->content;
	while (path)
	{
		link = ((t_vertex *)((t_list *)lst->content)->content)->link;
		vertex = (t_vertex *)path->content;
		if (ft_islinked(link, vertex))
		{
			if (lst->next && (lst->next->content != lst->content))
			{
				lst->next = ft_lstdup(tmp, 0);
				lst = lst->next;
			}
			tmp = lst->content;
			lst->content = ft_nodedup(path);	//copy end vertex to path
			((t_list *)lst->content)->next = tmp;
		}
		else
			lst = (lst->next) ? lst->next : list;
		path = ft_dequeue(path);
	}
	return (list);
}

/**
 * @brief search path with minimal length
 * @param graph
 * @return path list with min length
 */

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
			path = ft_addpath(path, (t_vertex *)queue->content);
			queue = ft_enqueue(queue, tmp->link, tmp->status + 1);
		}
		queue = ft_dequeue(queue);
	}
	ft_graphshow(1, graph);
	ft_queueshow(path);
	return (path);
}

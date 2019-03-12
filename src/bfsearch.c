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

// TODO universal condition for link adding

t_list				*ft_linkdup(t_vertex *vertex, int level)
{
	t_path	path;
	t_list	*lst;
	t_list	*new;
	t_list	*tmp;

	tmp = NULL;
	new = NULL;
	path.root = vertex;
	lst = vertex->link;
	while (lst)
	{
		if (lst->content_size < 1)
		{
			path.curr = lst->content;
			new = ft_lstnew(&path, sizeof(t_path));
			new->content_size = level;
			new->next = tmp;
			tmp = new;
		}
		lst = lst->next;
	}
	return (new);
}

t_list				*ft_enqueue(t_list *queue, t_vertex *vertex)
{
	t_list	*tmp;

	if (queue == NULL)
		queue = ft_linkdup(vertex, vertex->status + 1);
	else
	{
		tmp = queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_linkdup(vertex, vertex->status + 1);
	}
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

void				ft_delpath(t_list *path)
{
	t_list	*tmp;

	if (!path)
		return ;
	while (path)
	{
		tmp = path;
		path = path->next;
		ft_memdel((void **)&tmp);
	}
}

static t_list		*ft_shortestpath(t_graph *graph)
{
	t_list		*path;
	t_list		*node;
	t_vertex	*vertex;

	vertex = graph->end;
	path = NULL;
	while (vertex)
	{
		node = ft_memalloc(sizeof(t_list));
		node->content = vertex;
		node->next = path;
		path = node;
		if (vertex == graph->start)
			break;
		vertex = vertex->root;
	}
	return (path);
}

t_list				*ft_bfs(t_graph *graph)
{
	t_list		*queue;
	t_path		*tmp;

	if (!graph)
		return (0);
	graph->start->root = NULL;
	queue = ft_enqueue(NULL, graph->start);
	tmp = queue->content;
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
	return (ft_shortestpath(graph));
}

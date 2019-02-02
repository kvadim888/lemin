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

t_list		*ft_lstdup(t_list *lst)
{
	t_list	*new;
	t_list	*n;

	if (!lst)
		return (NULL);
	new = ft_memalloc(sizeof(t_list));
	new->content_size = lst->content_size;
	new->content = lst->content;
	n = new;
	lst = lst->next;
	while (lst)
	{
		n->next = ft_memalloc(sizeof(t_list));
		n->next->content_size = lst->content_size;
		n->next->content = lst->content;
		n = new->next;
		lst = lst->next;
	}
	return (new);
}

t_list		*ft_enqueue(t_list *queue, t_list *link)
{
	t_list	*q;

	q = queue;
	if (q)
	{
		while (q->next)
			q = q->next;
		q->next = ft_lstdup(link);
	}
	else
		queue = ft_lstdup(link);
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

void		ft_bfs(t_graph *graph)
{
	t_list		*queue;
	t_vertex	*tmp;

	if (!graph)
		return ;
	graph->start->status = 1;
	queue = ft_enqueue(NULL, graph->start->link);
	while ((t_vertex *)(queue->content) != graph->end)
	{
		tmp = (t_vertex *)queue->content;
		if (tmp->status == 0)
		{
			tmp->status = 1;
			queue = ft_enqueue(queue, tmp->link);
		}
		queue = ft_dequeue(queue);
	}
	if ((t_vertex *)(queue->content) == graph->end)
	tmp = (t_vertex *)queue->content;
	if (tmp->status == 0)
	{
		tmp->status = 1;
		queue = ft_enqueue(queue, tmp->link);
	}
	ft_dequeue(queue);
}

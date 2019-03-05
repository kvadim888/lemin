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

t_list		*ft_reducepath(t_graph *graph, t_list *path)
{
	t_list	*tmp;

	tmp = path;
	if (!path)
		return (NULL);
	while (0)
	{

	}
	return (path);
}

void		ft_addflow(t_list *path)
{
	t_list		*tmp;
	t_vertex	*curr;
	t_vertex	*next;
	t_list		*curr_link;
	t_list		*next_link;

	tmp = path;
	while (tmp)
	{
		curr = (t_vertex *)tmp->content;
		next = (t_vertex *)tmp->next->content;
		curr_link = curr->link->content;
		next_link = next->link->content;
		while (curr_link->content != next)
			curr_link = curr_link->next;
		while (next_link->content != curr)
			next_link = next_link->next;
		next_link->content_size -= 1;
		tmp = tmp->next;
	}
}

int			ft_edkarp(t_graph *graph)
{
	int		amount;
	t_list	*path;
	t_vertex	*vertex;

	amount = 0;
	while ((path = ft_reducepath(graph, ft_bfs(graph))) != NULL)
	{
		ft_addflow(path);
		while (path)
			path = ft_dequeue(path);
		vertex = graph->head;
		while (vertex)
		{
			vertex->status = 0;
			vertex = vertex->next;
		}
	}
	return (amount);
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

void		ft_delpair(t_vertex *vertex, t_list **link)
{
	t_vertex	*pair;
	t_list		*tmp;
	t_list		*prev;

	if (!(link && *link))
		return ;
	pair = (*link)->content;
	tmp = pair->link;
	prev = NULL;
	while (tmp && tmp->content != vertex)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	ft_cutlink(prev, tmp, pair);
	ft_memdel((void **)link);
}

t_vertex	*ft_cutvertex(t_vertex *vertex, t_vertex *prev)
{
	t_vertex	*tmp;
	t_list		*link;

	if (!vertex)
		return (NULL);
	tmp = vertex;
	vertex = vertex->next;
	if (prev)
		prev->next = vertex->next;
	while (tmp->link)
	{
		link = tmp->link;
		tmp->link = tmp->link->next;
		ft_delpair(vertex, &link);
	}
	ft_memdel((void **)&(tmp->link));
	ft_strdel(&(tmp->name));
	ft_memdel((void **)&tmp);
	return (vertex);
}

void		ft_graphreduce(t_graph *graph)
{
	t_vertex *vertex;
	t_vertex *prev;

	vertex = graph->head;
	prev = NULL;
	while (vertex)
	{
		if (vertex->status == 0)
			vertex = ft_cutvertex(vertex, prev);
		else
		{
			prev = vertex;
			vertex = vertex->next;
		}
	}
}

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

void		ft_addflow(t_list *link)
{
	t_vertex	*curr;
	t_vertex	*next;
	t_list		*curr_link;
	t_list		*next_link;

	curr = (t_vertex *)(link->content);
	next = (t_vertex *)(link->next->content);
	curr_link = ft_lstfind(curr->link, next, sizeof(next));
	next_link = ft_lstfind(next->link, curr, sizeof(curr));
	((t_route *)curr_link->content)->flow++;
	((t_route *)next_link->content)->flow--;
}

int			ft_flowcond(t_list *link, int flow)
{
	return (((t_route *)link->content)->flow == flow);
}

void 		ft_linkreduce(t_graph *graph, int (*cond)(t_list *, int))
{
	t_vertex	*vertex;
	t_list		*link;
	t_list		*prev;

	vertex = graph->head;
	while (vertex)
	{
		prev = NULL;
		link = vertex->link;
		while (link)
		{
			if (cond(link, 1))
			{
				prev = link;
				link = link->next;
			}
			else
				link = ft_cutlink(prev, link, vertex);
		}
		vertex = vertex->next;
	}
}

void 		ft_graphreduce(t_graph *graph)
{
	t_vertex	*vertex;
	t_vertex	*prev;

	prev = NULL;
	vertex = graph->head;
	while (vertex)
	{
		if ((vertex->link == NULL) &&
			!(vertex == graph->start || vertex == graph->end))
			vertex = ft_cutvertex(graph, prev, vertex);
		else
		{
		    prev = vertex;
			vertex = vertex->next;
		}
	}
}

int			ft_edkarp(t_graph *graph)
{
	t_list		*path;

	while ((path = ft_bfs(graph)) != NULL)
	{
		ft_lstiter(path, ft_addflow);
        ft_delpath(&path);
		ft_resetgraph(graph, 0);
		ft_lstiter(graph->head, ft_bfsreset);
	}
	ft_linkreduce(graph, ft_flowcond);
	ft_graphreduce(graph);
	ft_graphshow(1,graph);
	return (1);
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

t_vertex	*ft_cutvertex(t_graph *graph, t_vertex *prev, t_vertex *vertex)
{
	t_vertex	*tmp;

	tmp = vertex;
	vertex = vertex->next;
	if (prev)
		prev->next = vertex;
	else
		graph->head = vertex->next;
	ft_strdel(&(tmp->name));
	ft_memdel((void **)&tmp);
	return (vertex);
}

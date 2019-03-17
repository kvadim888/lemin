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

static int	ft_vertexcmp(void const *route, void const *vertex)
{
	return (((t_route const *)route)->vertex == vertex);
}

void		ft_addflow(t_list *link)
{
	t_vertex	*curr_vertex;
	t_vertex	*next_vertex;
	t_list		*curr_link;
	t_list		*next_link;

	if (link->next)
	{
		curr_vertex = (t_vertex *)(link->content);
		next_vertex = (t_vertex *)(link->next->content);
		curr_link = ft_lstfind(curr_vertex->link, next_vertex, ft_vertexcmp);
		next_link = ft_lstfind(next_vertex->link, curr_vertex, ft_vertexcmp);
		((t_route *)curr_link->content)->flow += 1;
		((t_route *)next_link->content)->flow -= 1;
	}
}

t_list		*ft_cutlink(t_list *link)
{
	t_list	*next;

	next = link->next;
	while (next && (((t_route *)next->content)->flow != 1))
	{
		link->next = next->next;
		ft_lstdelone(&next, ft_lstrm);
		next = link->next;
	}
	return (link);
}

void 		ft_linkreduce(t_list *lst)
{
	t_list	*link;

	link = ((t_vertex *)lst->content)->link;
	((t_vertex *)lst->content)->link = ft_lstmap(link, ft_cutlink);
	link = ((t_vertex *)lst->content)->link;
	ft_lstiter(link, ft_linkshow);
}

t_list		*ft_cutvertex(t_graph *graph, t_list *vertex)
{
	t_vertex	*v;
	t_list		*next;

	next = vertex->next;
	v = next->content;
	if ((v->link == NULL) && (v != graph->start) && (v != graph->end))
	{
		vertex->next = next->next;
		ft_lstdelone(&next, ft_lstrm);
		next = vertex->next;
	}
	else
	{
		vertex = vertex->next;
		vertex->next = next->next;
	}
	return (vertex);
}

void 		ft_graphreduce(t_graph *graph)
{
	t_list	vertex;
	t_list	tmp;

	vertex.next = graph->head;
	tmp.next = vertex.next;
	while (tmp.next)
		tmp.next = ft_cutvertex(graph, &tmp);
	graph->head = vertex.next;
}

int			ft_edkarp(t_graph *graph)
{
	t_list		*path;

	while ((path = ft_bfs(graph)) != NULL)
	{
		ft_lstiter(path, ft_addflow);
		ft_graphshow(graph);
		ft_lstiter(graph->head, ft_bfsreset);
        ft_lstdel(&path, ft_lstrm);
	}
	ft_lstiter(((t_vertex *)graph->head->content)->link, ft_linkshow);
	ft_lstiter(graph->head, ft_linkreduce);
	ft_lstiter(((t_vertex *)graph->head->content)->link, ft_linkshow);
//	ft_graphreduce(graph);
	ft_graphshow(graph);
	return (1);
}

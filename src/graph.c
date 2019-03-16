/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:55:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 17:55:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*ft_newvertex(char *name, int x, int y)
{
	t_vertex	vertex;

	vertex.name = ft_strdup(name);
	vertex.x = x;
	vertex.y = y;
	vertex.status = 0;
	vertex.root = NULL;
	vertex.link = NULL;
	return (ft_lstnew(&vertex, sizeof(t_vertex)));
}

t_vertex	*ft_findvertex(t_graph *graph, char *name)
{
	t_list		*tmp;
	t_vertex	*vertex;

	tmp = graph->head;
	while (tmp)
	{
		vertex = tmp->content;
		if (ft_strequ(vertex->name, name))
			return (vertex);
		tmp = tmp->next;
	}
	return (NULL);
}

int			ft_linkvertex(t_graph *graph, char *name1, char *name2)
{
	t_vertex	*v1;
	t_vertex	*v2;

	v1 = ft_findvertex(graph, name1);
	v2 = ft_findvertex(graph, name2);
	return (ft_newlink(v1, v2) && ft_newlink(v2, v1));
}

int			ft_newlink(t_vertex *v1, t_vertex *v2)
{
	t_route	route;

	if (!(v1 && v2) || ft_lstfind(v1->link, v2, sizeof(v2)))
		return (0);
	route.vertex = v2;
	route.flow = 0;
	ft_lstadd(&(v1->link), ft_lstnew(&route, sizeof(route)));
	return (1);
}

//		ft_lstiter(graph->head, ft_bfsreset);
//		ft_lstiter(graph->head, ft_edkarpreset);

void		ft_bfsreset(t_list *vertex)
{
	if (vertex)
	{
		((t_vertex *)vertex->content)->status = 0;
		((t_vertex *)vertex->content)->root = NULL;
	}
}

void		ft_linkreset(t_list *link)
{
	if (link)
	{
		((t_route *)link->content)->vertex = 0;
		((t_route *)link->content)->flow = 0;
	}
}

void		ft_edkarpreset(t_list *vertex)
{
	if (vertex)
	{
		((t_vertex *)vertex->content)->status = 0;
		((t_vertex *)vertex->content)->root = NULL;
		ft_lstiter(((t_vertex *)vertex->content)->link, ft_linkreset);
	}
}

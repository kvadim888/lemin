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

t_graph		*ft_newgraph(void)
{
	t_graph		*graph;

	if (!(graph = ft_memalloc(sizeof(t_graph))))
		return (NULL);
	graph->head = NULL;
	return (graph);
}

t_vertex	*ft_newvertex(char *name, int x, int y)
{
	t_vertex	*vertex;

	if (!(vertex = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	vertex->name = ft_strdup(name);
	vertex->x = x;
	vertex->y = y;
	vertex->status = 0;
	vertex->next = NULL;
	return (vertex);
}

void		ft_linkvertex(char *name1, char *name2, t_vertex *head)
{
	t_vertex	*tmp1;
	t_vertex	*tmp2;

	tmp1 = head;
	while (tmp1 && !(ft_strequ(tmp1->name, name1)))
		tmp1 = tmp1->next;
	tmp2 = head;
	while (tmp2 && !(ft_strequ(tmp2->name, name2)))
		tmp2 = tmp2->next;
	if (!tmp1 || !tmp2)
		return ;
	if (ft_newlink(tmp1, tmp2))
		ft_newlink(tmp2, tmp1);
}

int			ft_newlink(t_vertex *v1, t_vertex *v2)
{
	t_list	*link;

	if (!v1 || !v2)
		return (0);
	if (!(v1->link))
	{
		if (!(v1->link = ft_memalloc(sizeof(t_list))))
			return (0);
		v1->link->content = v2;
		v1->link->content_size = 0;
		v1->link->next = NULL;
		return (1);
	}
	link = v1->link;
	while (link->next && link->content != v2)
		link = link->next;
	if (link->next)
		return (0);
	if (!(link->next = ft_memalloc(sizeof(t_list))))
		return (0);
	link->next->content = v2;
	link->next->content_size = 0;
	link->next->next = NULL;
	return (1);
}

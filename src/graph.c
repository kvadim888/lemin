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
	graph->amount = 0;
	graph->head = NULL;
//	if (!(graph->head = ft_memalloc(sizeof(t_vertex *))))
//	{
//		ft_memdel((void **)&graph);
//		return (NULL);
//	}
	return (graph);
}

t_vertex	*ft_newvertex(char *name, int x, int y)
{
	t_vertex	*vertex;

	if (!(vertex = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	vertex->name = name;
	vertex->x = x;
	vertex->y = y;
	vertex->next = NULL;
	return (vertex);
}

t_list		*ft_newlink(t_vertex *vertex, t_vertex *head, char *name)
{
	t_list	*link;

	if (!vertex)
		return (NULL);
	while (head && !(ft_strequ(head->name, name)))
		head = head->next;
	if (!head)
		return (NULL);
	if (!(link = ft_memalloc(sizeof(t_list))))
		return (NULL);
	link->content = head;
	link->content_size = (size_t)((vertex->x - head->x) ^ 2
							  + (vertex->y - head->y) ^ 2);
	link->next = NULL;
	return (link);
}

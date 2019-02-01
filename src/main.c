/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:33:10 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:23 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int ac, char **av)
{
	int			fd;
	int			ants;
	t_graph		*graph;
	t_vertex	*tmp;
	t_vertex	*link;

	fd = open(av[1], O_RDONLY);
	graph = ft_newgraph();
	ants = ft_readfile(graph, fd);
	ft_dprintf(1, "ants = %d\n", ants);
	if (ants == 0)
		return (1);
	tmp = graph->head;
	while (tmp)
	{
		ft_dprintf(1, "name = %s; x = %d; y = %d\n", tmp->name, tmp->x, tmp->y);
		while (tmp->link)
		{
			link = (t_vertex *)(tmp->link->content);
			ft_dprintf(1, "[%s|%s]->", tmp->name, link->name);
			tmp->link = tmp->link->next;
		}
		ft_dprintf(1, "\n");
		tmp = tmp->next;
	}
	return (0);
}
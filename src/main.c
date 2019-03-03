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
	t_link		*path;
	t_graph		*graph;

	fd = open(av[1], O_RDONLY);
	graph = ft_newgraph();
	ants = ft_readfile(graph, fd);
	ft_printf("ants = %d\n", ants);
	if (ants == 0)
	{
		ft_dprintf(2, "ERROR\n");
		return (1);
	}
	ft_graphshow(1, graph);
	path = ft_bfs(graph);
	ft_graphreduce(graph);
	ft_queueshow(path);
	ft_graphshow(1, graph);
	ft_linkreduce(graph);
	printf("\n");
	ft_graphshow(1, graph);
	ft_moveants(graph, ants);
	return (0);
}

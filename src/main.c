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

	fd = open(av[1], O_RDONLY);
	system("leaks lem-in | grep -c Leak");
	graph = ft_newgraph();
	system("leaks lem-in | grep -c Leak");
	ants = ft_readfile(graph, fd);
	ft_dprintf(1, "ants = %d\n", ants);
	if (ants == 0)
		return (1);
	system("leaks lem-in | grep -c Leak");
	ft_graphshow(1, graph);
	ft_printf("\n");
	system("leaks lem-in | grep -c Leak");
	ft_bfs(graph);
	ft_printf("\n");
	system("leaks lem-in | grep -c Leak");
	ft_graphshow(1, graph);
	system("leaks lem-in | grep -c Leak");
	return (0);
}
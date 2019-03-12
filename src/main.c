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
	t_list		*path;
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
//	ft_graphshow(1, graph);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	ft_delpath(path);
//	ft_resetgraph(graph);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	ft_delpath(path);
//	ft_resetgraph(graph);
//	while (path)
//		path = ft_dequeue(path);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	while (path)
//		path = ft_dequeue(path);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	while (path)
//		path = ft_dequeue(path);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	while (path)
//		path = ft_dequeue(path);
//	ft_resetgraph(graph);
//	path = ft_bfs(graph);
//	ft_queueshow(path);
//	while (path)
//		path = ft_dequeue(path);
//	ft_resetgraph(graph);
//    ft_graphshow(1, graph);
	ft_graphshow(1, graph);
	ft_edkarp(graph);
	ft_graphshow(1, graph);
//	ft_addflow(path, 1);
//	ft_graphshow(1, graph);
	return (0);
}

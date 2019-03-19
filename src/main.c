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

t_list	*ft_vertexcopy(t_list *lst)
{
	return (ft_lstnew(lst->content, lst->content_size));
}

int		main(int ac, char **av)
{
	int			fd;
	int			ants;
	t_graph		graph;
	t_list		*path;
	t_list		**tmp;

	fd = open(av[1], O_RDONLY);
	ants = ft_readfile(&graph, fd);
	ft_printf("ants = %d\n", ants);
	if (ants == 0)
	{
		ft_dprintf(2, "ERROR\n");
		return (1);
	}
	ft_lstiter(graph.head, ft_vertexshow);
	ft_edkarp(&graph);
	ft_lstiter(graph.head, ft_vertexshow);
	ft_moveants(&graph,ants);
	system("leaks lem-in");
	return (0);
}

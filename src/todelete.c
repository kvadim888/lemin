/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todelete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:01:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:01:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

# define NORM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GREEN  "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE  "\x1B[34m"
# define MAGENTA  "\x1B[35m"
# define CYAN  "\x1B[36m"
# define WHITE  "\x1B[37m"

int		ft_graphshow(t_graph *graph)
{
	if (graph->head)
	{
		ft_lstiter(graph->head, ft_vertexshow);
		return (1);
	}
	return (0);
}

void	ft_vertexshow(t_list *lst)
{
	t_vertex	*vertex;

	vertex = lst->content;
//	if (graph->start == vertex)
//		printf("%sstart->%s", RED, NORM);
//	if (graph->end == vertex)
//		printf("%send->%s", RED, NORM);
	printf("%s(%d)%s[%s]%s[%s]%s:",
		   CYAN, vertex->status,
		   BLUE, vertex->name,
		   GREEN, (vertex->root) ? vertex->root->name : NULL, NORM);
	fflush(stdout);
	if (vertex->link)
		ft_lstiter(vertex->link, ft_linkshow);
	else
		printf("[null]\n");
}

void	ft_linkshow(t_list *lst)
{
	t_route	*route;

	if (lst->content)
	{
		route = lst->content;
		ft_printf("[%d|'%s']->", route->flow, route->vertex->name);
	}
	if (lst->next == NULL)
		printf("[null]\n");
}

void	ft_pathshow(t_list *lst)
{
	if (lst->content)
		ft_printf("[%s]", ((t_vertex *)lst->content)->name);
	if (lst->next)
		ft_printf("->");
	else
		printf("\n");
}

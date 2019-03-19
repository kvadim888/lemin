/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:55:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/04 19:55:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_printstep(t_list *lst)
{
	t_ant	*ant;

	ant = lst->content;
	if ((ant == NULL) || (ant->vertex == NULL))
		return ;
	ft_printf("L%d-%s", ant->number, ant->vertex->name);
	ant = lst->next->content;
	if (ant->vertex != NULL)
		ft_printf(" ");
	else
		ft_printf("\n");
}

void			ft_moveants(t_graph *graph, int num)
{
	t_list	*ants;
	t_list	*curr_ant;
	t_list	*link;

	ants = NULL;
	while (num-- > 0)
		ft_lstadd(&ants, ft_lstnew(&(t_ant){graph->start, num}, sizeof(t_ant)));
	curr_ant = ants;
	link = graph->start->link;
	while (curr_ant)
	{
		while (link)
		{
			next_vertex = ((t_route *)link->content)->vertex;
			((t_ant *)ants->content)->vertex = next_vertex;
		}
			link = link->next;
		if (link)
		{
			curr_ant->content = (t_vertex *)(link->content);
			((t_vertex *)link->content)->status = (int)curr_ant->content_size;
		}


		ft_printstep(ants);
		curr_ant = curr_ant->next;
	}
		curr_ant = curr_ant->next;
		curr_ant->content = link->content;
	ft_lstdel(&ants, NULL);
}

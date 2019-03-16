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

static t_list	*ft_makeants(size_t amount, t_vertex *init)
{
	t_list	*ants;

	ants = ft_lstnew(NULL, 0);
	ants->content_size = amount;
	while (--amount > 0)
	{
		ft_lstadd(&ants, ft_lstnew(init, 0));
		ants->content_size = amount;
	}
	return (ants);
}

static void		ft_printstep(t_list *ants)
{
	int		flag;
	t_list	*curr;

	curr = ants;
	flag = 0;
	while (curr)
	{
	    if (curr->content != NULL)
		{
			if (flag)
				ft_printf(" L%d-%s", curr->content_size,
						  ((t_vertex *)curr->content)->name);
			else
				ft_printf("L%d-%s", curr->content_size,
						  ((t_vertex *)curr->content)->name);
			flag = 1;
		}
		curr = curr->next;
	}
	ft_printf("\n");
}

void			ft_moveants(t_graph *graph, int amount)
{
	t_list	*ants;
	t_list	*curr_ant;
	t_list	*link;

	ants = ft_makeants(amount, graph->start);
	curr_ant = ants;
	link = graph->start->link;
	while (curr_ant)
	{
		while (link && ((t_vertex *)link->content)->status)
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

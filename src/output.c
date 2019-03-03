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

static t_list	*ft_makeants(int amount)
{
	t_list	*ants;

	ants = ft_lstnew(NULL, 0);
	ants->content_size = amount;
	while (--amount > 0)
	{
		ft_lstadd(&ants, ft_lstnew(NULL, amount));
		ants->content_size = amount;
	}
	return (ants);
}

static t_list	*ft_delants(t_list *ants)
{
	while (ants && (ants->content == NULL))
		ants = ft_dequeue(ants);
	return (ants);
}

static void		ft_printstep(t_list *ants)
{
	int		flag;
	t_list	*curr;

	curr = ants;
	flag = 0;
	while (curr && curr->content)
	{
		if (flag)
			ft_printf(" L%d-%s", curr->content_size,
					  ((t_vertex *)curr->content)->name);
		else
			ft_printf("L%d-%s", curr->content_size,
					  ((t_vertex *)curr->content)->name);
		flag = 1;
		curr = curr->next;
	}
	ft_printf("\n");
}

void			ft_moveants(t_graph *graph, int amount)
{
	t_list		*ants;
	t_list		*link;
	t_list		*curr_ant;

	ants = ft_makeants(amount);
	while (ants)
	{
		link = graph->start->link;
		curr_ant = ants;
		while (curr_ant && curr_ant->content)
		{
			curr_ant->content = (((t_vertex *)curr_ant->content)->link)
					? ((t_vertex *)curr_ant->content)->link->content : NULL;
			curr_ant = curr_ant->next;
		}
		while (link && curr_ant)
		{
			curr_ant->content = link->content;
			curr_ant = curr_ant->next;
			link = link->next;
		}
		ants = ft_delants(ants);
		ft_printstep(ants);
	}
}

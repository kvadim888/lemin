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

int			ft_graphshow(int out, t_graph *graph)
{
	t_vertex	*tmp;
	t_list		*list;
	t_vertex	*link;

	if (!graph)
		return (0);
	tmp = graph->head;
	while (tmp)
	{
		if (graph->start == tmp)
			dprintf(out, "%sstart->%s", RED, NORM);
		if (graph->end == tmp)
			dprintf(out, "%send->%s", RED, NORM);
		dprintf(out, "%s(%d)%s[\'%s\'; %d; %d]\n", CYAN, tmp->status, NORM,
													tmp->name, tmp->x, tmp->y);
		list = tmp->link;
		while (list)
		{
			link = (t_vertex *)(list->content);
			ft_dprintf(out, "[%s|%s]->", tmp->name, link->name);
			list = list->next;
		}
		dprintf(out, "[null]\n");
		tmp = tmp->next;
	}
	return (1);
}
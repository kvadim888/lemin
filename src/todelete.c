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

	if (!graph)
		return (0);
	tmp = graph->head;
	while (tmp)
	{
		if (graph->start == tmp)
			dprintf(out, "%sstart->%s", RED, NORM);
		if (graph->end == tmp)
			dprintf(out, "%send->%s", RED, NORM);
		dprintf(out, "%s(%d)%s[%s]%s[%s]%s:",
				CYAN, tmp->status,
				BLUE, tmp->name,
				GREEN, (tmp->root) ? tmp->root->name : NULL, NORM);
		list = tmp->link;
		while (list)
		{
			ft_dprintf(out, "[%d|'%s']->", list->content_size, ((t_vertex *)list->content)->name);
			list = list->next;
		}
		dprintf(out, "[null]\n");
		tmp = tmp->next;
	}
	return (1);
}

int			ft_antshow(t_list *ants)
{
	t_list	*tmp;

	if (!ants)
		return (0);
	tmp = ants;
	while (tmp)
	{
		ft_printf("[%d]->", tmp->content_size);
		tmp = tmp->next;
	}
	return (1);
}

int			ft_queueshow(t_list *queue)
{
	if (!queue)
		return (0);
	while (queue)
	{
		ft_printf("[%s]->", ((t_vertex *)queue->content)->name);
		queue = queue->next;
	}
	ft_printf("[null]\n");
	return (1);
}

int		ft_islinked(t_list *path, t_vertex *vertex)
{
	t_list	*p;

	if (!path || !vertex)
		return (0);
	p = path;
	while (p)
	{
		if (p->content == vertex)
			return (1);
		p = p->next;
	}
	return (0);
}

t_list		*ft_nodedup(t_list *node)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->content_size = node->content_size;
	new->content = node->content;
	new->next = NULL;
	return (new);
}


t_list		*ft_lstinsert(t_list *list, t_list *new)
{
	t_list	*tmp;

	if (!new && !list)
		return (NULL);
	if (!list)
		return (new);
	if (!new)
		return (list);
	tmp = list->next;
	list->next = new;
	new->next = tmp;
	return (new);
}

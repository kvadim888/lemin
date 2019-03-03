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
		dprintf(out, "%s(%d)%s[%s]%s:", CYAN,  tmp->status, BLUE, tmp->name, NORM);
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

t_list		*ft_lstdup(t_list *lst, int level)
{
	t_list	*new;
	t_list	*n;

	if (!lst)
		return (NULL);
	new = ft_memalloc(sizeof(t_list));
	new->content_size = (size_t)level;
	new->content = lst->content;
	n = new;
	lst = lst->next;
	while (lst)
	{
		n->next = ft_memalloc(sizeof(t_list));
		n->next->content_size = level;
		n->next->content = lst->content;
		n = n->next;
		n->next = NULL;
		lst = lst->next;
	}
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

t_list	*ft_pathsplit(t_list *path)
{
	t_list	*list;
	t_list	*link;
	t_list	*lst;
	t_list	*tmp;

	list = ft_memalloc(sizeof(t_list));			//list of paths
	list->content = ft_nodedup(path);			//copy end vertex to path
	path = ft_dequeue(path);
	lst = list;
	tmp = lst->content;
	while (path)
	{
		printf("path{%s}\n", ((t_vertex *)path->content)->name);
		ft_printf("vertex{%s} ", ((t_vertex *)tmp->content)->name);
		link = ((t_vertex *)tmp->content)->link;
		ft_queueshow(link);
		if (ft_islinked(link, (t_vertex *)path->content))
		{
			printf("{%s} linked with {%s}\n", ((t_vertex *)path->content)->name,
				   ((t_vertex *)tmp->content)->name);
			if (lst->content != tmp)
			{
				lst = ft_lstinsert(lst, ft_lstnew(NULL, 0));
				lst->content = ft_lstdup(tmp, 0);
				tmp = lst->content;
			}
			lst->content = ft_nodedup(path);	//copy end vertex to path
			((t_list *)lst->content)->next = tmp;
			path = ft_dequeue(path);
		}
		else
		{
			lst = (lst->next) ? lst->next : list;
			tmp = lst->content;
		}
	}
	return (list);
}


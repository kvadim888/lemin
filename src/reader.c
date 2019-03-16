/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:59:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 10:59:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_unique(t_graph *graph, t_vertex *vertex)
{
	t_list		*tmp;
	t_vertex	*v;

	if (!graph || !graph->head)
		return (vertex != NULL);
	tmp = graph->head;
	while (tmp)
	{
		v = (t_vertex *)tmp->content;
		if (ft_strequ(vertex->name, v->name)
			|| ((vertex->x == v->x) && (v->y == vertex->y)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int 		ft_fillgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	vertex;
	int			label;

	label = 0;
	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		if (**str != '#')
		{
			if (!ft_validvertex(*str, &vertex) && !ft_unique(graph, &vertex))
				return (0);
			ft_strdel(str);
			ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
			if (label == 1)
				graph->start = graph->head->content;
			if (label == 2)
				graph->end = graph->head->content;
			label = 0;
		}
		else
			label = (label == 0) ? ft_label(*str) : label;
	}
	return (1);
}

int 		ft_linkgraph(t_graph *graph, int fd, char **str)
{
	char	*name1;
	char	*name2;
	int		stat;

	while (*str)
	{
		if (**str != '#')
		{
			if (!ft_islink(*str))
				return (0);
			name1 = ft_strsub(*str, 0, ft_strchr(*str, '-') - *str);
			name2 = ft_strchr(*str, '-') + 1;
			stat = ft_linkvertex(graph, name1, name2);
			ft_strdel(&name1);
			if (stat == 0)
				return (0);
		}
		ft_strdel(str);
		if (get_next_line(fd, str) < 1)
			return (1);
	}
	return (0);
}

int			ft_readfile(t_graph *graph, int fd)
{
	int		i;
	int		stat;
	char	*str;
	int		ants;

	if (get_next_line(fd, &str) < 0)
		return (0);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	ants = (str[i] == '\0') ? ft_atoi(str) : 0;
	ft_strdel(&str);
	if (ants <= 0)
		return (0);
	stat = 0;
	if (ft_fillgraph(graph, fd, &str))
		stat = ft_linkgraph(graph, fd, &str);
	ft_strdel(&str);
	return ((stat) ? ants : 0);
}

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

int			ft_addvertex(t_graph *graph, t_vertex *vertex, int label)
{
	t_vertex	*tmp;

	if (!graph->head)
		graph->head = vertex;
	else
	{
		tmp = graph->head;
		while (tmp)
		{
			if (ft_strequ(vertex->name, tmp->name)
				|| ((tmp->x == vertex->x) && (tmp->y == vertex->y)))
				return (0);
			if (tmp->next == NULL)
			{
				tmp->next = vertex;
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (label == 1)
		graph->start = vertex;
	if (label == 2)
		graph->end = vertex;
	return (1);
}

void		ft_delvertex(t_vertex **vertex)
{
	if (*vertex)
	{
		ft_strdel(&((*vertex)->name));
		ft_memdel((void **)vertex);
	}
}

int 		ft_fillgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	*tmp;
	int			label;
	char 		*name;
	int 		x;
	int 		y;

	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		if (ft_iscomment(str, &label))
			continue ;
		name = NULL;
		tmp = (ft_validvertex(*str, &name, &x, &y))
				? ft_newvertex(name, x, y) : NULL;
		ft_strdel(&name);
		ft_strdel(str);
		if (tmp == NULL)
			return (0);
		if (!ft_addvertex(graph, tmp, label))
		{
			ft_delvertex(&tmp);
			return (0);
		}
		label = 0;
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
			{
				return (0);
			}
			name1 = ft_strsub(*str, 0, ft_strchr(*str, '-') - *str);
			name2 = ft_strchr(*str, '-') + 1;
			stat = ft_linkvertex(name1, name2, graph->head);
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

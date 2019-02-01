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

static int	ft_checkname(char *name)
{
	// TODO: add dash checking
	if (!name || ft_strlen(name) == 0)
		return (0);
	if (*name == 'L')
		return (0);
	return (1);
}

char 		*ft_fillgraph(t_graph *graph, int fd)
{
	t_vertex	*tmp;
	char		*str;
	int			label;
	char		**buff;

	label = 0;
	while (get_next_line(fd, &str) > 0 && !(ft_strchr(str, '-')))
	{
		if (*str == '#')
		{
			label = (ft_strequ(str, "##start")) ? 1 : label;
			label = (ft_strequ(str, "##end")) ? 2 : label;
			continue;
		}
		buff = ft_strsplit(str, ' ');
		tmp = graph->head;
		graph->head = ft_newvertex(buff[0], ft_atoi(buff[1]), ft_atoi(buff[2]));
		graph->head->next = tmp;
		if (label == 1)
			graph->start = graph->head;
		if (label == 2)
			graph->end = graph->head;
	}
	return (str);
}

int 		ft_linkgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	*tmp;
	char		**name;

	while (get_next_line(fd, str) > 0)
	{
		if (**str == '#')
			continue ;
		name = ft_strsplit(*str, '-');
		tmp = graph->head;
		while (tmp && !(ft_strequ(tmp->name, name[0])))
			tmp = tmp->next;
		if (!tmp)
			continue ;
		if (!(tmp->link))
			tmp->link = ft_newlink(tmp, graph->head, name[1]);
		else
		{
			while (tmp->link->next)
			{
				if (ft_strequ(((t_vertex *)tmp->link->content)->name, name[1]))
					break;
				tmp->link = tmp->link->next;
			}
			if (!(tmp->link->next))
				tmp->link->next = ft_newlink(tmp, graph->head, name[1]);
		}
	}
	return (1);
}

int			ft_readfile(t_graph *graph, int fd)
{
	char	*str;
	int		i;
	int		ants;

	if (get_next_line(fd, &str) < 1)
		return (0);
	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	ants = ft_atoi(str);
	ft_strdel(&str);
	if (!(str = ft_fillgraph(graph, fd)))
		return (0);
	if (!ft_linkgraph(graph, fd, &str))
		return (0);
	return (ants);
}

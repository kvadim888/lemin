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

int			ft_readants(int fd, char **str)
{
	int		ants;
	int		i;

	if ((get_next_line(fd, str) < 0) || ft_strlen(*str) == 0)
		return (0);
	i = 0;
	while (ft_isdigit((*str)[i]))
		i++;
	ants = (i == ft_strlen(*str)) ? ft_atoi(*str) : 0;
	ft_strdel(str);
	return (ants);
}

static int	ft_cmp(void const *vertex1, void const *vertex2)
{
	if (ft_strequ(((t_vertex*)vertex1)->name, ((t_vertex*)vertex2)->name))
		return (1);
	if (((t_vertex*)vertex1)->x == ((t_vertex*)vertex2)->x &&
		((t_vertex*)vertex1)->y == ((t_vertex*)vertex2)->y)
		return (1);
	return (0);
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
			ft_readvertex(*str, &vertex);
			if (ft_lstfind(graph->head, &vertex, ft_cmp))
			{
				ft_strdel(str);
				return (0);
			}
			ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
			if (label == 1)
				graph->start = graph->head->content;
			if (label == 2)
				graph->end = graph->head->content;
			label = 0;
		}
		else
			label = (label == 0) ? ft_label(*str) : label;
		ft_strdel(str);
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
	int		stat;
	char	*str;
	int		ants;

	if ((ants = ft_readants(fd, &str)) == 0)
		ft_error(ANTS);
	if ((stat = ft_fillgraph(graph, fd, &str)) == 1)
		stat = ft_linkgraph(graph, fd, &str);
	// TODO: check begin and end
	// TODO: check link between begin and end
	ft_strdel(&str);
	return ((stat) ? ants : 0);
}

void ft_error(char const *msg)
{
	ft_dprintf(2, "ERROR: %s\n", msg);
	exit(0);
}

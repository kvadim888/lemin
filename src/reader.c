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

int			ft_validvertex(char *str, char **name, int *x, int *y)
{
	int		i;

	if (str[0] == 'L')
		return (0);
	i = -1;
	while ((str[++i] != '\0') && (str[i] != ' ') && (str[i] != '-'))
		i++;
	if ((str[i] == '\0') || (str[i] == '-'))
		return (0);
	*name = ft_strsub(str, 0, (size_t)i);
	str += (i + 1);
	i = (str[0] == '-') ? 1 : 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[0] != ' ')
		return (0);
	*x = ft_atoi(str);
	str += (i + 1);
	i = (str[0] == '-') ? 1 : 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	*y = ft_atoi(str);
	return (1);
}

int			ft_comment(char *str, int *label)
{
	if (*str == '#')
	{
		if (ft_strequ(str, "##start"))
			*label = 1;
		if (ft_strequ(str, "##end"))
			*label = 2;
		return (1);
	}
	return (0);
}

int 		ft_fillgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	*tmp;
	int			label;
	char 		*name;
	int 		x;
	int 		y;

	while (get_next_line(fd, str) > 0 && !(ft_strchr(*str, '-')))
	{
		if (ft_comment(*str, &label))
			continue ;
		tmp = NULL;
		if (ft_validvertex(*str, &name, &x, &y))
			tmp = ft_newvertex(name, x, y);
		ft_strdel(&name);
		if (!tmp)
			return (0);
		tmp->next = graph->head;
		graph->head = tmp;
		if (label == 2)
			graph->start = graph->head;
		if (label == 3)
			graph->end = graph->head;
		ft_strdel(str);
	}
	return (1);
}

int 		ft_linkgraph(t_graph *graph, int fd, char **str)
{
	char	*name1;
	char	*name2;

	while (get_next_line(fd, str) > 0)
	{
		if (**str == '#')
		{
			ft_strdel(str);
			continue ;
		}
		name1 = ft_strsub(*str, 0, ft_strchr(*str, '-') - *str);
		name2 = ft_strchr(*str, '-') + 1;
		ft_linkvertex(name1, name2, graph->head);
		ft_strdel(str);
		ft_strdel(&name1);
	}
	ft_strdel(str);
	return (1);
}

int			ft_readfile(t_graph *graph, int fd)
{
	char	*str;
	int		i;
	int		ants;

	if (get_next_line(fd, &str) < 1)
	{
		ft_strdel(&str);
		return (0);
	}
	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			ft_strdel(&str);
			return (0);
		}
	}
	ants = ft_atoi(str);
	ft_strdel(&str);
	if (ft_fillgraph(graph, fd, &str))
		return (0);
	if (!ft_linkgraph(graph, fd, &str))
		return (0);
	return (ants);
}

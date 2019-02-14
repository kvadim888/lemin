/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:34:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/03 17:34:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_iscomment(char **str, int *label)
{
	if (**str == '#')
	{
		if (ft_strequ(*str, "##start"))
			*label = 1;
		if (ft_strequ(*str, "##end"))
			*label = 2;
		ft_strdel(str);
		return (1);
	}
	return (0);
}

int			ft_islink(char *str)
{
	if ((*str != '#') && !ft_strchr(str, ' ') && ft_strchr(str, '-'))
		return (1);
	return (0);
}

int			ft_validvertex(char *str, char **name, int *x, int *y)
{
	int		i;

	if (str[0] == 'L')
		return (0);
	i = 0;
	while ((str[i] != '\0') && (str[i] != ' ') && (str[i] != '-'))
		i++;
	if ((str[i] == '\0') || (str[i] == '-'))
		return (0);
	*name = ft_strsub(str, 0, (size_t)i);
	str += (i + 1);
	i = (str[0] == '-') ? 1 : 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ')
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

//int			ft_validlink(char *str, t_graph *graph, char **name1, char **name2)
//{
//	int			i;
//	t_vertex	*tmp;
//
//	i = 0;
//	while ((str[i] != '\0') && (str[i] != '-'))
//		i++;
//	if (str[i] == '\0')
//		return (0);
//	*name1 = ft_strsub(str, 0, (size_t)i);
//	str += (i + 1);
//	*name2 = ft_strdup(str);
//	tmp = graph->head;
//	while (tmp && !ft_strcmp(tmp->name, *name1))
//		tmp = tmp->next;
//	if (tmp == NULL)
//		return (0);
//	tmp = graph->head;
//	while (tmp && !ft_strcmp(tmp->name, *name2))
//		tmp = tmp->next;
//	if (tmp == NULL)
//		return (0);
//	return (1);
//}

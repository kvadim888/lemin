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

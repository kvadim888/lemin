/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 11:00:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 11:00:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

typedef struct			s_vertex
{
	char				*name;
	int					x;
	int					y;
	t_list				*link;
	struct s_vertex		*next;
}						t_vertex;

t_vertex	*ft_newvertex(char *name, int x, int y);
t_list		*ft_newlink(t_vertex *vertex, t_vertex *head, char *name);

typedef	struct			s_graph
{
	int					amount;
	t_vertex			*head;
	t_vertex			*start;
	t_vertex			*end;
}						t_graph;

t_graph		*ft_newgraph(void);

int			ft_readfile(t_graph *graph, int fd);

#endif

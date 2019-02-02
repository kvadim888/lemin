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
	int					status;
	int					x;
	int					y;
	t_list				*link;
	struct s_vertex		*next;
}						t_vertex;

t_vertex				*ft_newvertex(char *name, int x, int y);
void					ft_linkvertex(char *name1, char *name2, t_vertex *head);
int						ft_newlink(t_vertex *v1, t_vertex *v2);

typedef	struct			s_graph
{
	t_vertex			*head;
	t_vertex			*start;
	t_vertex			*end;
}						t_graph;

t_graph					*ft_newgraph(void);
int						ft_fillgraph(t_graph *graph, int fd, char **str);
int						ft_linkgraph(t_graph *graph, int fd, char **str);
int						ft_readfile(t_graph *graph, int fd);

t_list					*ft_lstdup(t_list *lst);
t_list					*ft_enqueue(t_list *queue, t_list *link);
void					ft_bfs(t_graph *graph);

/*
 *  TO DELETE -- additional functions for convenience
 */

int			ft_graphshow(int out, t_graph *graph);

#endif

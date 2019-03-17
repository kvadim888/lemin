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
	struct s_vertex		*root;
}						t_vertex;

typedef	struct			s_graph
{
	t_list				*head;
	t_vertex			*start;
	t_vertex			*end;
}						t_graph;

typedef struct			s_route
{
	struct s_vertex		*vertex;
	int					flow;
}						t_route;

t_list					*ft_newvertex(char *name, int x, int y);
int						ft_linkvertex(t_graph *graph, char *name1, char *name2);
int						ft_newlink(t_vertex *v1, t_vertex *v2);


void					ft_resetgraph(t_graph *graph, int reset_links);
int						ft_fillgraph(t_graph *graph, int fd, char **str);
int						ft_linkgraph(t_graph *graph, int fd, char **str);
int						ft_readfile(t_graph *graph, int fd);

void					ft_addflow(t_list *link);

t_list					*ft_bfs(t_graph *graph);
int						ft_edkarp(t_graph *graph);

int						ft_label(char *str);
int						ft_islink(char *str);
int						ft_validvertex(char *str, t_vertex *vertex);

void					ft_delpath(t_list **path);

void					ft_moveants(t_graph *graph, int amount);


void					ft_bfsreset(t_list *vertex);
void					ft_linkreset(t_list *link);
void					ft_edkarpreset(t_list *vertex);

/*
 *  TO DELETE -- additional functions for convenience
 */

int						ft_graphshow(t_graph *graph);
int						ft_queueshow(t_list *queue);
t_list					*ft_pathsplit(t_list *path);
int						ft_antshow(t_list *ants);

void					ft_linkshow(t_list *lst);
void					ft_pathshow(t_list *lst);

#endif

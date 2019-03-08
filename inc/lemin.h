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
	struct s_vertex		*root;
}						t_vertex;

typedef struct			s_path
{
	struct s_vertex		*root;
	struct s_vertex		*curr;
}						t_path;

t_vertex				*ft_newvertex(char *name, int x, int y);
int						ft_linkvertex(char *name1, char *name2, t_vertex *head);
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

t_list					*ft_linkdup(t_list *lst, t_vertex *vertex, int level);
t_list					*ft_enqueue(t_list *queue, t_vertex *vertex);
t_list					*ft_dequeue(t_list *queue);
t_list					*ft_nodedup(t_list *node);
t_list					*ft_bfs(t_graph *graph);
int						ft_edkarp(t_graph *graph);
t_list					*ft_shortestpath(t_graph *graph);
void					ft_addflow(t_list *path, int flow);

t_list					*ft_trace(t_vertex *vertex, t_list *prev, t_list **trace);

int						ft_iscomment(char **str, int *label);
int						ft_islink(char *str);
int						ft_validvertex(char *str, char **name, int *x, int *y);
//int					ft_validlink(char *str, t_graph *graph,
//												char **name1, char **name2);

void					ft_moveants(t_graph *graph, int amount);

/*
 *  TO DELETE -- additional functions for convenience
 */

int						ft_graphshow(int out, t_graph *graph);
int						ft_queueshow(t_list *queue);
t_list					*ft_pathsplit(t_list *path);
int						ft_antshow(t_list *ants);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 12:33:53 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 13:31:02 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>

# define ERROR -1
# define NORMAL 0
# define START 1
# define END 2
# define COMMENT 3

# define MULTI_WAY 1
# define COLOR 2
# define TRIP 4
# define WAY 8
# define PRINT_WAY 16
# define DETAIL 32

# define MAX_NODE 255

char						*g_mem_line;

typedef struct				s_node
{
	char					*name;
	int						len_end;
	int						weight;
	int						passed;
	int						sorted;
	int						nb_move;
	unsigned int			i_tab;
	unsigned int			index;
	long long int			x;
	long long int			y;
	struct s_node			*adj[MAX_NODE];
	struct s_node			*way;
	struct s_node			*mem;
	struct s_node			*next;
}							t_node;

typedef struct				s_lem_in
{
	unsigned char			flags;
	int						nb_ant;
	unsigned int			nb_room;
	t_node					*anthill;
	t_node					*start;
	t_node					*end;
}							t_lem_in;

typedef struct				s_ant
{
	char					*color;
	char					*reset;
	unsigned int			name;
	unsigned int			nb_way;
	unsigned int			nb_move;
	t_node					*way;
	t_node					*curs;
	struct s_ant			*next;
}							t_ant;

t_lem_in					*make_node(void);
void						print_lem_in(t_lem_in *lem_in);
int							get_nb_ant(unsigned char flags);
t_lem_in					*del_lem_in(t_lem_in **lem_in);
t_node						*del_node(t_node **anthill);
int							link_node(t_lem_in *lem);
int							lem_in(t_lem_in *lem);
int							sort_lem_int(t_lem_in **lem);
int							move_ants(unsigned int nb_ant, t_node *way,
		unsigned char flags);
t_node						*inverse_liste(t_node *lst, unsigned char flags);
void						print_nodes(t_node *lst);
void						print_ant(t_ant *ant, unsigned char flags);
void						*detail_error(char *str, unsigned char flags);

#endif

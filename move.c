/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 11:27:25 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 10:48:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant				*new_ant(unsigned int name, t_node *way,
		unsigned int nb_way)
{
	static int				loop = 0;
	t_ant					*new;

	if ((new = ft_memalloc(sizeof(t_ant))) == NULL)
		return (NULL);
	if (loop == 0 || loop == 1)
		new->color = ft_strdup(loop == 0 ? "\033[0;31m" : "\033[0;32m");
	else if (loop == 2 || loop == 3)
		new->color = ft_strdup(loop == 2 ? "\033[0;33m" : "\033[0;34m");
	else if (loop == 4 || loop == 5)
		new->color = ft_strdup(loop == 4 ? "\033[0;35m" : "\033[0;36m");
	new->reset = ft_strdup("\033[0;0m");
	loop = (loop + 1) > 5 ? 0 : loop + 1;
	new->name = name;
	new->way = way;
	new->curs = new->way->way;
	new->nb_way = nb_way;
	return (new);
}

static t_ant				*make_ant(unsigned int nb_ant, t_node *way,
		unsigned int nb_way)
{
	unsigned int			i;
	t_ant					*ant;
	t_ant					*curs;
	t_ant					*new;

	ant = NULL;
	i = 0;
	while (i < nb_ant)
	{
		if ((new = new_ant(i++, way, nb_way)) == NULL)
			break ;
		if (ant == NULL)
			ant = new;
		else
		{
			curs = ant;
			while (curs->next != NULL)
				curs = curs->next;
			curs->next = new;
		}
	}
	return (ant);
}

static void					del_ant(t_ant **ant)
{
	t_ant					*tmp;

	if (ant != NULL)
		while (*ant != NULL)
		{
			tmp = (*ant)->next;
			ft_memdel((void**)&(*ant)->color);
			ft_memdel((void**)&(*ant)->reset);
			ft_memdel((void**)ant);
			*ant = tmp;
		}
	ft_memdel((void**)ant);
}

int							print_line(unsigned int nb_print, t_ant *ant,
		unsigned char flags)
{
	int						fin;
	t_ant					*curs;

	curs = ant;
	fin = 1;
	while (nb_print-- > 0 && curs != NULL)
	{
		if (curs->curs != NULL)
			fin = 0;
		print_ant(curs, flags);
		curs = curs->next;
	}
	return (fin);
}

int							move_ants(unsigned int nb_ant, t_node *way,
		unsigned char flags)
{
	int						fin;
	unsigned int			nb_print;
	t_ant					*ant;

	ft_putchar('\n');
	fin = 0;
	nb_print = 0;
	way = inverse_liste(way, flags);
	if ((ant = make_ant(nb_ant, way, 1)) != NULL)
		while (fin == 0)
			if ((fin = print_line(++nb_print, ant, flags)) != 1)
				ft_putchar('\n');
	del_ant(&ant);
	return (1);
}

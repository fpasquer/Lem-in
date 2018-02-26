/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:28:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/09 11:03:51 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int					forget_node(t_node **anthill, t_node **node)
{
	t_node					*curs;
	t_node					*curs_pres;

	curs = *anthill;
	curs_pres = NULL;
	while (curs != NULL)
	{
		if (curs == (*node))
		{
			if (curs_pres == NULL)
				(*anthill) = curs->next;
			else
				curs_pres->next = curs->next;
			return (1);
		}
		curs_pres = curs;
		curs = curs->next;
	}
	return (0);
}

void						print_node(t_node *node)
{
	t_node					*curs;

	curs = node;
	while (curs != NULL)
	{
		ft_putendl(curs->name);
		curs = curs->next;
	}
}

int							sort_lem_int(t_lem_in **lem)
{
	t_node				*curs;

	if (forget_node(&(*lem)->anthill, &(*lem)->start) == 0)
		return (0);
	if (forget_node(&(*lem)->anthill, &(*lem)->end) == 0)
		return (0);
	(*lem)->start->next = (*lem)->anthill;
	(*lem)->start->sorted = 1;
	(*lem)->anthill = (*lem)->start;
	curs = (*lem)->anthill;
	while (curs->next != NULL)
		curs = curs->next;
	(*lem)->end->next = NULL;
	curs->next = (*lem)->end;
	return (1);
}

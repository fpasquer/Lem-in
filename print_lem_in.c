/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:26:01 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/09 13:57:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					print_tube(char *name1, char *name2)
{
	ft_putstr(name1);
	ft_putchar('-');
	ft_putendl(name2);
}

static void					print_lem_in2(t_lem_in *lem_in)
{
	unsigned int			i;
	t_node					*cpy;

	cpy = lem_in->anthill;
	while (cpy != NULL)
	{
		if (cpy != lem_in->start && cpy != lem_in->end)
		{
			ft_putstr(cpy->name);
			ft_putchar(' ');
			ft_putnbr(cpy->x);
			ft_putchar(' ');
			ft_putnbr(cpy->y);
			ft_putchar('\n');
		}
		cpy = cpy->next;
	}
	cpy = lem_in->anthill;
	while (cpy != NULL)
	{
		i = 0;
		while (i < cpy->i_tab)
			print_tube(cpy->name, cpy->adj[i++]->name);
		cpy = cpy->next;
	}
}

void						print_lem_in(t_lem_in *lem_in)
{
	ft_putnbr(lem_in->nb_ant);
	ft_putstr("\n##start\n");
	ft_putstr(lem_in->start->name);
	ft_putchar(' ');
	ft_putnbr(lem_in->start->x);
	ft_putchar(' ');
	ft_putnbr(lem_in->start->y);
	ft_putstr("\n##end\n");
	ft_putstr(lem_in->end->name);
	ft_putchar(' ');
	ft_putnbr(lem_in->end->x);
	ft_putchar(' ');
	ft_putnbr(lem_in->end->y);
	ft_putchar('\n');
	print_lem_in2(lem_in);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 20:02:53 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 11:04:11 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					print_way(t_node *lst)
{
	static unsigned int		nb_loop = 1;
	t_node					*curs;

	curs = lst;
	ft_putstr("Way nb :");
	ft_putnbr(nb_loop++);
	ft_putchar('\n');
	while (curs != NULL)
	{
		ft_putstr(curs->name);
		ft_putchar(' ');
		curs = curs->way;
	}
	ft_putstr("\n\n");
}

t_node						*inverse_liste(t_node *lst, unsigned char flags)
{
	t_node					*tmp1;
	t_node					*tmp2;

	if (lst != NULL)
	{
		tmp1 = lst->way;
		lst->way = NULL;
		while (tmp1 != NULL)
		{
			tmp2 = tmp1->way;
			tmp1->way = lst;
			lst = tmp1;
			tmp1 = tmp2;
		}
	}
	if ((flags & WAY) != 0)
		print_way(lst);
	return (lst);
}

void						print_ant(t_ant *ant, unsigned char flags)
{
	if (ant->curs == NULL)
		return ;
	if ((flags & COLOR) != 0)
		ft_putstr(ant->color);
	ft_putchar('L');
	ft_putnbr(ant->name + 1);
	ant->nb_move++;
	if ((flags & TRIP) != 0)
	{
		ft_putstr("[");
		if ((flags & TRIP) != 0)
			ft_putnbr(ant->nb_move);
		ft_putstr("]");
	}
	if ((flags & PRINT_WAY) != 0)
	{
		ft_putstr(" : ");
		ft_putnbr(ant->nb_way);
	}
	ft_putchar('-');
	ft_putstr(ant->curs->name);
	ft_putchar(' ');
	ant->curs = ant->curs->way;
	if ((flags & COLOR) != 0)
		ft_putstr(ant->reset);
}

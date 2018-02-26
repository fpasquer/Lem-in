/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 12:33:58 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 16:36:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned int			g_mem_len = 0;

static int					del_grid(int ***grid, unsigned int y)
{
	unsigned int			i;

	i = 0;
	while (i < y)
		ft_memdel((void**)&(*grid)[i++]);
	ft_memdel((void**)grid);
	return (-1);
}

static t_node				*mem_way(t_node *way)
{
	unsigned int			len_way;
	t_node					*curs_way;
	t_node					*curs_mem;
	static t_node			*mem = NULL;

	if (way == NULL)
		return (mem);
	len_way = 0;
	curs_way = way;
	while (curs_way != NULL && ++len_way)
		curs_way = curs_way->mem;
	if (len_way > g_mem_len && g_mem_len != 0)
		return (mem);
	g_mem_len = len_way;
	mem = way;
	curs_way = way;
	curs_mem = mem;
	while (curs_way->mem != NULL)
	{
		curs_mem->way = curs_way->mem;
		curs_mem = curs_mem->way;
		curs_way = curs_way->mem;
	}
	return (mem);
}

static t_node				*save_way_end(t_node **node, unsigned int lvl,
		t_lem_in *lem)
{
	unsigned int			i;
	t_node					*curs;
	static t_node			*way = NULL;

	curs = (way == NULL) ? *node : way;
	way = *node;
	if (curs != *node)
		way->mem = curs;
	way->passed = 1;
	if ((*node) == lem->end)
		mem_way(way);
	i = 0;
	while (i < (*node)->i_tab && (*node) != lem->end)
	{
		if (g_mem_len != 0 && lvl >= g_mem_len)
			break ;
		if ((*node)->adj[i++]->passed == 0)
			way = save_way_end(&(*node)->adj[i - 1], lvl + 1, lem);
	}
	way->passed = (way != NULL && way->mem != NULL) ? 0 : way->passed;
	way = (way != NULL && way->mem != NULL) ? way->mem : way;
	return (way);
}

/*
**static void					print_flags(t_lem_in *lem)
**{
**	printf("MULTI_WAY = %s\n", (lem->flags & MULTI_WAY) != 0 ? "OUI": "NON");
**	printf("COLOR = %s\n", (lem->flags & COLOR) != 0 ? "OUI": "NON");
**	printf("TRIP = %s\n", (lem->flags & TRIP) != 0 ? "OUI": "NON");
**	printf("WAY = %s\n", (lem->flags & WAY) != 0 ? "OUI" : "NON");
**	printf("PRINT_WAY = %s\n", (lem->flags & PRINT_WAY) != 0 ? "OUI": "NON");
**	}
*/

int							lem_in(t_lem_in *lem)
{
	int						**grid;
	unsigned int			y;
	t_node					*curs;

	if ((grid = ft_memalloc(sizeof(int *) * lem->nb_room)) == NULL)
		return (-1);
	y = 0;
	while (y < lem->nb_room)
		if ((grid[y++] = ft_memalloc(sizeof(int) * lem->nb_room)) == NULL)
			return (del_grid(&grid, y - 1));
	save_way_end(&lem->anthill, 0, lem);
	if ((curs = mem_way(NULL)) == NULL)
		return (0);
	move_ants(lem->nb_ant, curs, lem->flags);
	del_grid(&grid, y);
	return (1);
}

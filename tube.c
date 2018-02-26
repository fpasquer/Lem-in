/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:58:35 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 13:50:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int					make_link(t_node **a, t_node **b)
{
	if ((*a) == NULL || (*b) == NULL)
		return (-1);
	(*a)->adj[(*a)->i_tab++] = (*b);
	(*b)->adj[(*b)->i_tab++] = (*a);
	if ((*a)->i_tab >= MAX_NODE || (*b)->i_tab >= MAX_NODE)
		return (-2);
	return (1);
}

static int					link_a_b(t_lem_in *lem, char *line)
{
	char					**split;
	int						ret;
	t_node					*tab[2];
	t_node					*curs;

	if ((split = ft_strsplit(line, '-')) == NULL)
		return (0);
	ret = 0;
	if (len_y(split) == 2)
	{
		curs = lem->anthill;
		while (curs != NULL && ft_strcmp(curs->name, split[0]) != 0)
			curs = curs->next;
		tab[0] = curs;
		curs = lem->anthill;
		while (curs != NULL && ft_strcmp(curs->name, split[1]) != 0)
			curs = curs->next;
		tab[1] = curs;
		ret = make_link(&tab[0], &tab[1]);
	}
	ft_free_strsplit(split);
	return (ret);
}

int							link_node(t_lem_in *lem)
{
	char					*line;
	int						ret;

	if (g_mem_line != NULL)
	{
		if ((ret = link_a_b(lem, g_mem_line)) <= 0)
			return (ret);
		ft_memdel((void**)&g_mem_line);
	}
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (line == NULL || line[0] == '\0')
			break ;
		ft_putendl(line);
		if (line[0] != '#')
			if ((ret = link_a_b(lem, line)) <= 0)
				return (ret);
		ft_memdel((void**)&line);
	}
	return (1);
}

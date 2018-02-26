/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 13:02:48 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 17:40:37 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define M mode

static t_node				*g_end = NULL;
static t_node				*g_start = NULL;

static t_node				*save_node(char *name, char *x, char *y,
		unsigned char flags)
{
	t_node					*new;

	if (ft_is_number(x) != 1 || ft_is_number(y) != 1 || name[0] == 'L')
		return (detail_error("Wrong format", flags));
	if ((new = ft_memalloc(sizeof(t_node))) == NULL)
		return (detail_error("Malloc new", flags));
	if ((new->name = ft_strdup(name)) == NULL)
		return (detail_error("Dup name", flags));
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	new->weight = -1;
	return (new);
}

static int					get_mode(char *line, t_lem_in *lem)
{
	static int				found_end = 0;
	static int				found_start = 0;

	ft_putendl(line);
	if (line[0] == '#')
	{
		if (ft_strcmp(line, "##start") == 0)
			return (found_start++ == 0 ? START : ERROR);
		if (ft_strcmp(line, "##end") == 0)
			return (found_end++ == 0 ? END : ERROR);
		if (ft_strcmp(line, "#m") == 0)
			lem->flags = lem->flags == 0 ? MULTI_WAY : lem->flags | MULTI_WAY;
		else if (ft_strcmp(line, "#c") == 0)
			lem->flags = lem->flags == 0 ? COLOR : lem->flags | COLOR;
		else if (ft_strcmp(line, "#t") == 0)
			lem->flags = lem->flags == 0 ? TRIP : lem->flags | TRIP;
		else if (ft_strcmp(line, "#w") == 0)
			lem->flags = lem->flags == 0 ? WAY : lem->flags | WAY;
		else if (ft_strcmp(line, "#pw") == 0)
			lem->flags = lem->flags == 0 ? PRINT_WAY : lem->flags | PRINT_WAY;
		return (COMMENT);
	}
	else
		return (NORMAL);
}

static t_node				*new_node(t_lem_in *lem)
{
	char					*line;
	char					**split;
	int						mode[2];
	int						mode_prev;
	t_node					*ret;

	mode[1] = NORMAL;
	ret = NULL;
	while ((mode[0] = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		mode_prev = (mode[1] == COMMENT) ? mode_prev : mode[1];
		if ((mode[1] = get_mode(line, lem)) <= NORMAL)
			break ;
		ft_memdel((void**)&line);
	}
	if (M[0] <= 0 || M[1] == ERROR || (split = ft_strsplit(line, ' ')) == NULL)
		return (detail_error("Wrong format", lem->flags));
	if (len_y(split) == 3)
		ret = save_node(split[0], split[1], split[2], lem->flags);
	g_mem_line = len_y(split) != 3 ? ft_strdup(line) : g_mem_line;
	g_end = mode_prev == END && ret != NULL ? ret : g_end;
	g_start = mode_prev == START && ret != NULL ? ret : g_start;
	ft_free_strsplit(split);
	ft_memdel((void**)&line);
	return (ret);
}

static t_node				*save_anthill(unsigned int *nb_room, t_lem_in *lem)
{
	unsigned int			loop;
	t_node					*anthill;
	t_node					*curs;
	t_node					*new;

	anthill = NULL;
	loop = 0;
	while (1)
	{
		if ((new = new_node(lem)) == NULL)
			break ;
		new->index = loop;
		if (anthill == NULL)
			anthill = new;
		else
			curs->next = new;
		curs = new;
		loop++;
	}
	*nb_room = loop;
	return (anthill);
}

t_lem_in					*make_node(void)
{
	t_lem_in				*new;

	if ((new = ft_memalloc(sizeof(t_lem_in))) == NULL)
		return (detail_error("malloc new", DETAIL));
	if ((new->nb_ant = get_nb_ant(DETAIL)) == 0)
		return (del_lem_in(&new));
	if ((new->anthill = save_anthill(&new->nb_room, new)) == NULL)
		return (del_lem_in(&new));
	if (g_end == NULL || g_start == NULL)
		return (del_lem_in(&new));
	new->start = g_start;
	new->end = g_end;
	if (sort_lem_int(&new) == 0)
		return (del_lem_in(&new));
	if (link_node(new) <= 0)
		return (del_lem_in(&new));
	if (new->start->adj[0] == NULL || new->end->adj[0] == NULL)
		return (del_lem_in(&new));
	new->start->weight = 0;
	return (new);
}

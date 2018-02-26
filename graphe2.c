/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphe2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:31:12 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 17:29:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node						*del_node(t_node **anthill)
{
	t_node					*tmp;

	if (anthill != NULL)
	{
		while ((*anthill) != NULL)
		{
			tmp = (*anthill)->next;
			ft_memdel((void**)&(*anthill)->name);
			ft_memdel((void**)&(*anthill));
			(*anthill) = tmp;
		}
		ft_memdel((void**)anthill);
	}
	return (NULL);
}

t_lem_in					*del_lem_in(t_lem_in **lem_in)
{
	if (lem_in != NULL && *lem_in != NULL)
	{
		del_node(&(*lem_in)->anthill);
		ft_memdel((void**)lem_in);
	}
	return (NULL);
}

int							get_nb_ant(unsigned char flags)
{
	char					*line;
	int						nb_ant;
	int						ret;

	line = NULL;
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		ft_putendl(line);
		if (line[0] != '#')
			break ;
		ft_memdel((void**)&line);
	}
	if (line == NULL)
		return ((int)detail_error("line = NULL", flags));
	if (ret <= 0)
		return ((int)detail_error("EOF", flags));
	if (ft_is_number(line) != 1)
		return ((int)detail_error("Wrong number of ant", flags));
	nb_ant = ft_atoi(line);
	ft_memdel((void**)&line);
	if (nb_ant < 1)
		return ((int)detail_error("Negatif ou 0 number of ant", flags));
	return (nb_ant);
}

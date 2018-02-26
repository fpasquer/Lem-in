/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 12:34:05 by fpasquer          #+#    #+#             */
/*   Updated: 2016/05/10 11:58:48 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void						*detail_error(char *str, unsigned char flags)
{
	if ((flags & DETAIL) != 0)
		ft_putendl(str);
	return (NULL);
}

void						error(void)
{
	ft_putstr("ERROR\n");
	exit(0);
}

int							main(void)
{
	int						ret;
	t_lem_in				*lem;

	if ((lem = make_node()) == NULL)
		error();
	ret = lem_in(lem);
	del_lem_in(&lem);
	if (ret == 0)
		error();
	return (0);
}

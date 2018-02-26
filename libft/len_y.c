/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:27:34 by fpasquer          #+#    #+#             */
/*   Updated: 2016/03/12 20:44:18 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t					len_y(char **tab)
{
	size_t				y;

	if (tab == NULL)
		return (0);
	y = 0;
	while (tab[y] != NULL)
		y++;
	return (y);
}
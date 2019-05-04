/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_insert_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:53:44 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/04 12:54:11 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstr_insert_c(t_lstr *lstr, char c, int index)
{
	if (lstr == NULL || index < 0 || index > lstr->length)
		return ;
	if (lstr->capacity < lstr->length + 2)
		if (!ft_lstr_resize(lstr, lstr->length + 1))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + 1, lstr->str + index,
			lstr->length - pos);
	lstr->str[pos] = c;
	++lstr->length;
}

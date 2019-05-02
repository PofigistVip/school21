/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_add_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:29:05 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:29:09 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

int		ft_lstr_add_c(t_lstr *lstr, char c)
{
	if (lstr == NULL)
		return (0);
	if (lstr->capacity - 2 < lstr->length)
		if (ft_lstr_resize(lstr->length + 1) == 0)
			return (0);
	lstr->str[lstr->length++] = c;
	lstr->str[lstr->length] = '\0';
	return (1);
}

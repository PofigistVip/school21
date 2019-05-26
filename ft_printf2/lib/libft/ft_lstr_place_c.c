/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_place_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:38:06 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 14:38:10 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstr_place_c(t_lstr *lstr, char c, int count, int index)
{
	if (lstr == NULL || count <= 0 || index < 0 || index > lstr->length)
		return ;
	if (index + count >= lstr->capacity)
	{
		if (ft_lstr_resize(lstr, index + count) == 0)
			return ;
		lstr->length = index + count;
	}
	ft_memset(lstr->str + index, c, count);
}

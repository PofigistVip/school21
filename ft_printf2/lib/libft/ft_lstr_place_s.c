/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_place_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:38:26 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 14:38:32 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstr_place_s(t_lstr *lstr, char *str, int index)
{
	int		len;

	if (lstr == NULL || str == NULL || index < 0 || index > lstr->length)
		return ;
	len = (int)ft_strlen(str);
	if (len == 0)
		return ;
	if (index + len >= lstr->capacity)
	{
		if (ft_lstr_resize(lstr, lstr->length - index + len) == 0)
			return ;
		lstr->length = index + len;
	}
	ft_memmove(lstr->str + index, str, len);
}

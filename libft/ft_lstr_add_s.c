/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_add_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:45:25 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:45:29 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_lstr_add_s(t_lstr *lstr, char *str)
{
	size_t	len;

	if (lstr == NULL)
		return (0);
	len = ft_strlen(str);
	if (lstr->capacity - 1 < lstr->length + len)
		if (ft_lstr_resize(lstr, lstr->length + len) == 0)
			return (0);
	ft_memcpy(lstr->str + lstr->length, str, len);
	lstr->length += len;
	lstr->str[lstr->length] = '\0';
	return (1);
}

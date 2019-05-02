/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_from_raw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:20:38 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:20:40 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_lstr	*ft_lstr_from_raw(char *str)
{
	t_lstr	*lstr;
	size_t	len;

	len = ft_strlen(str);
	if (len == 0)
		return (ft_lstr_empty());
	if ((lstr = (t_lstr*)malloc(sizeof(t_lstr))) == NULL)
		return (NULL);
	if ((lstr->str = (ft_strnew(len))) == NULL)
		return (NULL);
	ft_memcpy(lstr->str, str, len);
	return (lstr);
}

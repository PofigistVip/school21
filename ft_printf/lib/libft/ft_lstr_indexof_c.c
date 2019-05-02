/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_indexof_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:51:47 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:51:49 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstr_indexof_c(t_lstr *lstr, char c)
{
	int		i;
	char	*ptr;

	if (lstr == NULL)
		return (-2);
	i = 0;
	ptr = lstr->str;
	while (i < lstr->length)
	{
		if (*ptr == c)
			return (i);
		++ptr;
		++i;
	}
	return (-1);
}

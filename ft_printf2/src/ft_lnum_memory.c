/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnum_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:34:49 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 13:34:54 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void			ft_lnum_destroy(t_longnumber **lnum)
{
	if (lnum && *lnum)
	{
		free(*lnum);
		*lnum = NULL;
	}
}

t_longnumber	*ft_lnum_new_zero(void)
{
	t_longnumber	*lnum;

	if ((lnum = (t_longnumber*)malloc(sizeof(t_longnumber))) == NULL)
		return (NULL);
	lnum->is_decimal = 0;
	lnum->dec_end_on = 0;
	ft_memset(lnum->digits, 0, sizeof(lnum->digits));
	return (lnum);
}

t_longnumber	*ft_lnum_new_copy(t_longnumber *src)
{
	t_longnumber	*lnum;
	int				i;

	if ((lnum = (t_longnumber*)malloc(sizeof(t_longnumber))) == NULL)
		return (NULL);
	lnum->is_decimal = src->is_decimal;
	lnum->dec_end_on = src->dec_end_on;
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
		lnum->digits[i] = src->digits[i];
	return (lnum);
}

t_longnumber	*ft_lnum_new_int(int number)
{
	t_longnumber	*lnum;

	if ((lnum = ft_lnum_new_zero()) == NULL)
		return (NULL);
	lnum->digits[0] = number;
	ft_lnum_calc(lnum, 0);
	return (lnum);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnum_math2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:44:34 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:44:45 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_longnumber	*ft_lnum_pow(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	t_longnumber	*copy_a;
	t_longnumber	*copy_b;

	copy_a = ft_lnum_new_copy(a);
	copy_b = ft_lnum_new_copy(b);
	lnum = ft_lnum_new_int(1);
	while (ft_lnum_dec(copy_b))
		lnum = ft_lnum_mul(lnum, copy_a, 1, 0);
	ft_lnum_destroy(&copy_a);
	ft_lnum_destroy(&copy_b);
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

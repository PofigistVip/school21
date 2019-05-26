/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnum_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:43:24 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 13:43:25 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_lnum_dec(t_longnumber *lnum)
{
	--lnum->digits[0];
	return (ft_lnum_calc(lnum, 0));
}

t_longnumber	*ft_lnum_add(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	int				i;

	lnum = ft_lnum_new_copy(a);
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		lnum->digits[i] += b->digits[i];
		ft_lnum_calc(lnum, i);
	}
	lnum->dec_end_on = (a->dec_end_on < b->dec_end_on) ?
		a->dec_end_on : b->dec_end_on;
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_sub(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	int				i;

	lnum = ft_lnum_new_copy(a);
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		lnum->digits[i] -= b->digits[i];
		ft_lnum_calc(lnum, i);
	}
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_mul(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	t_longnumber	*copy_a;
	t_longnumber	*copy_b;

	copy_b = ft_lnum_new_copy(b);
	if (!ft_lnum_dec(copy_b))
	{
		ft_lnum_destroy(&copy_b);
		return (ft_lnum_new_zero());
	}
	lnum = ft_lnum_new_copy(a);
	copy_a = ft_lnum_new_copy(a);
	while (ft_lnum_dec(copy_b))
		lnum = ft_lnum_add(lnum, copy_a, 1, 0);
	ft_lnum_destroy(&copy_a);
	ft_lnum_destroy(&copy_b);
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_mul_int(t_longnumber *a, int b, int dst_a)
{
	t_longnumber	*lnum;
	t_longnumber	*copy_a;

	if (b <= 0)
		return (ft_lnum_new_zero());
	lnum = ft_lnum_new_copy(a);
	copy_a = ft_lnum_new_copy(a);
	while (--b)
		lnum = ft_lnum_add(lnum, copy_a, 1, 0);
	ft_lnum_destroy(&copy_a);
	if (dst_a)
		ft_lnum_destroy(&a);
	return (lnum);
}

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

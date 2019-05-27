/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_f_big_f_part3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:41:50 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:42:06 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_longnumber	*ft_lnum_pow2(int power)
{
	t_longnumber	*res;
	t_longnumber	*copy;

	if (power == 0)
		return (ft_lnum_new_int(1));
	if (power == 1)
		return (ft_lnum_new_int(2));
	res = ft_lnum_new_int(2);
	copy = ft_lnum_new_int(2);
	--power;
	while (power > 0)
	{
		res = ft_lnum_mul(res, copy, 1, 0);
		--power;
	}
	ft_lnum_destroy(&copy);
	return (res);
}

t_longnumber	*ft_lnum_pow5(int power)
{
	t_longnumber	*res;
	t_longnumber	*copy;

	if (power == 0)
		return (ft_lnum_new_int(1));
	if (power == 1)
		return (ft_lnum_new_int(5));
	res = ft_lnum_new_int(5);
	copy = ft_lnum_new_int(5);
	--power;
	while (power > 0)
	{
		res = ft_lnum_mul(res, copy, 1, 0);
		--power;
	}
	ft_lnum_destroy(&copy);
	return (res);
}

t_lstr			*ft_get_lnum(t_longnumber **lnum, t_longnumber **temp, int dec)
{
	t_lstr	*dec_part;

	dec_part = ft_lstr_new_raw((dec) ? ft_lnum_get_dec(*lnum) :
		ft_lnum_get(*lnum));
	ft_lnum_destroy(lnum);
	ft_lnum_destroy(temp);
	return (dec_part);
}

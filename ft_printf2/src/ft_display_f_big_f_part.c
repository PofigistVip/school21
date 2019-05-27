/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_f_big_f_part.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:37:03 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:37:05 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_lstr			*ft_get_decimal(int mant, __uint128_t fraction)
{
	int				pos;
	t_lstr			*dec_part;

	pos = 0;
	if (mant >= 64)
		return (ft_lstr_new('0', 1));
	if (mant >= 0)
	{
		pos = 62 - mant;
		mant = -1;
	}
	else
		pos = 63;
	fraction = fraction >> 64;
	dec_part = ft_get_dec(mant, fraction, pos, 0);
	return (dec_part);
}

int				ft_f_get_normal(int mant, __uint128_t fraction,
					t_lstr **int_p, t_lstr **dec_p)
{
	*int_p = ft_get_integer(mant, fraction);
	*dec_p = ft_get_decimal(mant, fraction);
	return (0);
}

int				ft_f_get_subnormal(__uint128_t fraction,
					t_lstr **int_p, t_lstr **dec_p)
{
	int				pos;
	int				mant;

	mant = -16382;
	pos = 63;
	*int_p = ft_lstr_new('0', 1);
	fraction = fraction >> 64;
	*dec_p = ft_get_dec(mant, fraction, pos, 1);
	return (0);
}

void			ft_f_round(t_lstr *int_p, t_lstr *dec_p, int precision)
{
	int		i;
	char	curr;

	if (dec_p->str[precision] >= '5' && dec_p->length - 1 != precision)
	{
		curr = 10;
		i = precision - 1;
		while (curr / 10 != 0 && i >= 0)
		{
			curr = (dec_p->str[i] - '0') + 1;
			dec_p->str[i] = (curr % 10) + '0';
			--i;
		}
		i = int_p->length - 1;
		while (curr / 10 != 0)
		{
			curr = (int_p->str[i] - '0') + 1;
			int_p->str[i] = (curr % 10) + '0';
			--i;
		}
	}
	ft_lstr_resize(dec_p, precision);
	dec_p->length = precision;
}

void			ft_get_sign_mantissa_fraction(long double val,
					t_double_keeper *keeper)
{
	__uint128_t	sig;
	__int128_t	manti;
	__uint128_t	fract;

	sig = 0;
	manti = 0;
	fract = 0;
	ft_memcpy(&sig, &val, 10);
	sig = sig & ((__uint128_t)1 << 79);
	ft_memcpy(&manti, &val, 10);
	manti = ((__uint128_t)(manti << 49)) >> 113;
	ft_memcpy(&fract, &val, 10);
	fract = (fract << 64);
	keeper->sign = sig;
	keeper->mantissa = manti;
	keeper->fraction = fract;
}

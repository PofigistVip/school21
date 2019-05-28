/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_f_big_f_part2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:38:48 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:39:18 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_lstr			*ft_get_integer(int mant, __uint128_t fraction)
{
	t_longnumber	*lnum;
	t_longnumber	*temp;
	size_t			pos;
	t_lstr			*int_part;

	fraction = fraction >> 64;
	pos = (64 - mant - 1 < 0) ? 0 : 64 - mant - 1;
	lnum = ft_lnum_new_zero();
	temp = 0;
	mant -= 63 - pos;
	while (lnum && pos < 64)
	{
		if (!temp)
			temp = ft_lnum_pow2(mant);
		else
			temp = ft_lnum_mul_int(temp, 2, 1);
		if (temp == NULL)
			break ;
		if (fraction & ((__uint128_t)1 << pos))
			lnum = ft_lnum_add(lnum, temp, 1, 0);
		++mant;
		pos++;
	}
	int_part = ft_get_lnum(&lnum, &temp, 0);
	return (int_part);
}

int				ft_count_zeroes(int mantissa)
{
	long double		dbl;
	int				cnt;
	__int128_t		mant;

	mant = (((__uint128_t)mantissa) << 64) | ((__uint128_t)1 << 63);
	ft_memcpy(&dbl, &mant, 10);
	cnt = -1;
	while (dbl < 1)
	{
		dbl *= 10;
		++cnt;
	}
	return (cnt);
}

int				ft_subnormal_count_zeroes(int one_pos)
{
	long double		dbl;
	int				cnt;
	__uint128_t		fraction;

	fraction = ((__uint128_t)1 << one_pos);
	ft_memcpy(&dbl, &fraction, 10);
	cnt = -1;
	while (dbl < 1)
	{
		dbl *= 10;
		++cnt;
	}
	return (cnt);
}

void			ft_temp_set(t_longnumber **temp, int mant)
{
	if (!(*temp))
		*temp = ft_lnum_pow5(-mant);
	else
		*temp = ft_lnum_mul_int(*temp, 5, 1);
}

t_lstr			*ft_get_dec(int mant, __uint128_t fraction, int pos,
					int subnormal)
{
	t_longnumber	*lnum;
	t_longnumber	*temp;
	t_longnumber	*tmp;
	int				zeroes;

	lnum = ft_lnum_new_zero();
	ft_lnum_make_decimal(&lnum, 0);
	temp = 0;
	while (lnum && pos >= 0)
	{
		ft_temp_set(&temp, mant);
		if (fraction & ((__uint128_t)1 << pos))
		{
			if ((tmp = ft_lnum_new_copy(temp)) == NULL)
				break ;
			zeroes = (subnormal) ? ft_subnormal_count_zeroes(pos) :
				ft_count_zeroes(mant + 16383);
			ft_lnum_make_decimal(&tmp, zeroes);
			lnum = ft_lnum_add(lnum, tmp, 1, 1);
		}
		--mant;
		--pos;
	}
	return (ft_get_lnum(&lnum, &temp, 1));
}

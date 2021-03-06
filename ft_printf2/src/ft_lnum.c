/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnum_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:02:11 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 15:02:14 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int				ft_lnum_calc(t_longnumber *lnum, int pos)
{
	int value;

	if (lnum == NULL)
		return (0);
	value = lnum->digits[pos];
	if (value < 0)
	{
		if (pos + 1 == FT_LONGNUMBER_SIZE)
			return (0);
		value = -value;
		lnum->digits[pos + 1] -= (value / FT_LONGNUMBER_BASE) + 1;
		lnum->digits[pos] = ((value / FT_LONGNUMBER_BASE) + 1) *
			FT_LONGNUMBER_BASE - value;
		return (ft_lnum_calc(lnum, pos + 1));
	}
	value = lnum->digits[pos] / FT_LONGNUMBER_BASE;
	if (value >= 1)
	{
		if (pos + 1 == FT_LONGNUMBER_SIZE)
			return (0);
		lnum->digits[pos + 1] += value;
		lnum->digits[pos] %= FT_LONGNUMBER_BASE;
		return (ft_lnum_calc(lnum, pos + 1));
	}
	return (1);
}

int				ft_lnum_length(t_longnumber *lnum)
{
	int	i;
	int	length;
	int temp;

	if (lnum == NULL)
		return (0);
	length = 0;
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		if (lnum->digits[i] != 0)
		{
			temp = lnum->digits[i];
			length = 1;
			while ((temp /= 10) != 0)
				length++;
			length += i * FT_LONGNUMBER_DIG_ON_INT;
			break ;
		}
	}
	if (i == -1)
		length = 1;
	return (length);
}

void			ft_lnum_make_decimal(t_longnumber **lnum, int shift)
{
	int				length;
	int				offset;
	int				big_offset;
	int				min_offset;
	t_longnumber	*supp;

	if (lnum == NULL || *lnum == NULL || (supp = ft_lnum_new_int(10)) == NULL)
		return ;
	length = ft_lnum_length(*lnum);
	offset = FT_LONGNUMBER_SIZE * FT_LONGNUMBER_DIG_ON_INT - shift - length;
	big_offset = offset / FT_LONGNUMBER_DIG_ON_INT;
	min_offset = offset % FT_LONGNUMBER_DIG_ON_INT;
	(*lnum)->dec_end_on = big_offset;
	ft_memmove((*lnum)->digits + big_offset, (*lnum)->digits, sizeof(int) *
		(FT_LONGNUMBER_SIZE - big_offset));
	ft_memset((*lnum)->digits, 0, big_offset * sizeof(int));
	while (min_offset--)
		*lnum = ft_lnum_mul(*lnum, supp, 1, 0);
	ft_lnum_destroy(&supp);
}

char			*ft_lnum_get(t_longnumber *lnum)
{
	char	*str;
	int		length;
	int		i[2];
	int		temp;

	if (lnum == NULL)
		return (NULL);
	length = ft_lnum_length(lnum);
	if ((str = (char*)malloc(sizeof(char) * (length + 1))) == NULL)
		return (NULL);
	str[length--] = '\0';
	i[0] = 0;
	while (length >= 0)
	{
		i[1] = 0;
		temp = lnum->digits[i[0]];
		while (length >= 0 && i[1] < FT_LONGNUMBER_DIG_ON_INT)
		{
			str[length--] = (temp % 10) + '0';
			temp /= 10;
			++i[1];
		}
		++i[0];
	}
	return (str);
}

char			*ft_lnum_get_dec(t_longnumber *lnum)
{
	char	*str;
	int		length;
	int		i[2];
	int		temp;

	if (lnum == NULL)
		return (NULL);
	length = (FT_LONGNUMBER_SIZE - lnum->dec_end_on) * FT_LONGNUMBER_DIG_ON_INT;
	if ((str = (char*)malloc(sizeof(char) * (length + 1))) == NULL)
		return (NULL);
	str[length--] = '\0';
	i[0] = lnum->dec_end_on;
	while (length >= 0)
	{
		i[1] = 0;
		temp = lnum->digits[i[0]];
		while (length >= 0 && i[1] < FT_LONGNUMBER_DIG_ON_INT)
		{
			str[length--] = (temp % 10) + '0';
			temp /= 10;
			++i[1];
		}
		++i[0];
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_test1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:37:40 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/07 10:37:42 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_activebits(int num)
{
	int i;
	int	first;
	int last;

	first = -1;
	last = -2;
	i = 0;
	while (i < 32)
	{
		if ((num & 1) == 1)
		{
			if (first == -1)
				first = i;
			else
				last = i;
		}
		++i;
		num = num >> 1;
	}
	return (last - first + 1);
}

void	ft_putwchar_inner(t_lstr *lstr, unsigned int v)
{
	unsigned char octet;

	octet = ((unsigned int)4034953344 >> 24) | (((v >> 18)  << 29) >> 29);
	ft_lstr_insert_c(lstr, octet, 1, lstr->length);
	octet = (((unsigned int)4034953344 << 8) >> 24) | (((v >> 12)  << 26) >> 26);
	ft_lstr_insert_c(lstr, octet, 1, lstr->length);
	octet = (((unsigned int)4034953344 << 16) >> 24) | (((v >> 6)  << 26) >> 26);
	ft_lstr_insert_c(lstr, octet, 1, lstr->length);
	octet = (((unsigned int)4034953344 << 24) >> 24) | ((v  << 26) >> 26);
	ft_lstr_insert_c(lstr, octet, 1, lstr->length);
}

void	ft_putwchar(t_lstr *lstr, wchar_t wc)
{
	int	nbits;
	unsigned int v;
	unsigned char octet;
	
	v = wc;
	if ((nbits = ft_activebits(wc)) <= 7)
		ft_lstr_insert_c(lstr, wc, 1, lstr->length);
	else if (nbits <= 11)
	{
		octet = ((unsigned int)49280 >> 8) | (((v >> 6) << 27) >> 27);
		ft_lstr_insert_c(lstr, octet, 1, lstr->length);
		octet = (((unsigned int)49280 << 24) >> 24) | ((v << 26) >> 26);
		ft_lstr_insert_c(lstr, octet, 1, lstr->length);	
	}
	else if (nbits <= 16)
	{
		octet = ((unsigned int)14712960 >> 16) | (((v >> 12) << 28) >> 28);
		ft_lstr_insert_c(lstr, octet, 1, lstr->length);
		octet = (((unsigned int)14712960 << 16) >> 24) | (((v >> 6) << 26) >> 26);
		ft_lstr_insert_c(lstr, octet, 1, lstr->length);
		octet = (((unsigned int)14712960 << 24) >> 24) | ((v << 26) >> 26);
		ft_lstr_insert_c(lstr, octet, 1, lstr->length);
	}
	else
		ft_putwchar_inner(lstr, v);
}
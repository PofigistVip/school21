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

#include <unistd.h>
#include <wchar.h>
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

void	ft_putwchar(wchar_t wc)
{
	int	nbits;
	unsigned int v;
	unsigned char octet;
	
	v = wc;
	nbits = ft_activebits(wc);
	if (nbits <= 7)
		write(1, &wc, 1);
	else if (nbits <= 11)
	{
		octet = ((unsigned int)49280 >> 8) | (((v >> 6) << 27) >> 27);
		write(1, &octet, 1);
		octet = (((unsigned int)49280 << 24) >> 24) | ((v << 26) >> 26);
		write(1, &octet, 1);	
	}
	else if (nbits <= 16)
	{
		octet = ((unsigned int)14712960 >> 16) | (((v >> 12) << 28) >> 28);
		write(1, &octet, 1);
		octet = (((unsigned int)14712960 << 16) >> 24) | (((v >> 6) << 26) >> 26);
		write(1, &octet, 1);
		octet = (((unsigned int)14712960 << 24) >> 24) | ((v << 26) >> 26);
		write(1, &octet, 1);
	}
	else
	{
		octet = ((unsigned int)4034953344 >> 24) | (((v >> 18)  << 29) >> 29);
		write(1, &octet, 1);
		octet = (((unsigned int)4034953344 << 8) >> 24) | (((v >> 12)  << 26) >> 26);
		write(1, &octet, 1);
		octet = (((unsigned int)4034953344 << 16) >> 24) | (((v >> 6)  << 26) >> 26);
		write(1, &octet, 1);
		octet = (((unsigned int)4034953344 << 24) >> 24) | ((v  << 26) >> 26);
		write(1, &octet, 1);
	}
}
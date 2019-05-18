#include <unistd.h>
#include "ft_printf.h"
#include <stdint.h>

void	show_binary(void *vptr, int count)
{
	char	*ptr;
	unsigned char	mask;

	ptr = (char*)vptr;
	ptr += count / 8 - 1;
	while (count > 0)
	{
		
		mask = (1 << 7);
		while (mask != 0 && count > 0)
		{
			if (*ptr & mask)
				ft_putchar('1');
			else
				ft_putchar('0');
			--count;
			mask = mask >> 1;
		}
		--ptr;
	}
}
#include <stdio.h>
int		ft_display_fF(int fd, t_printf_elem *el)
{
	double	val;
	char	sign;
	long long int	mantissa;
	int				mant;
	uint64_t		fraction;
	uint64_t		integer;
	uint64_t		decimal;

	val = el->arg->val_d;
	sign = (val < 0) ? -1 : 1;
	ft_memcpy(&mantissa, &val, 8);
	mantissa = ((unsigned long long int)(mantissa << 1)) >> 53;
	//normal way
	mant = mantissa - 1023;
	ft_memcpy(&fraction, &val, 8);
	fraction = ((fraction << 12) >> 12) | 4503599627370496;
	integer = fraction >> (52 - mant);
	decimal = (fraction << 11);
	show_binary(&fraction, 64);
	ft_putchar('\n');
	show_binary(&decimal, 64);
	(void)fd;
	(void)sign;
	return (0);
}
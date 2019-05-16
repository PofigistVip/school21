#include <unistd.h>
#include "ft_printf.h"

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

	val = el->arg->val_d;
	sign = (val < 0) ? -1 : 1;
	ft_memcpy(&mantissa, &val, 8);
	mantissa = ((unsigned long long int)(mantissa << 1)) >> 53;
	show_binary(&mantissa, 64);
	(void)fd;
	(void)sign;
	return (0);
}
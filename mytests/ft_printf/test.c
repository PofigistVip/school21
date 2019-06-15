#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "ft_printf.h"
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <locale.h>

#define FMT "%#x", 256

int		main(void)
{
	int		len;
	char	char1 = 'a';
	char	*str1 = "Larlyne";
	int		int1 = 5;
	int		int2 = 2;
	double dbl = 0;
	uint64_t bigint = (1ULL);// | (1ULL << 1) | (1ULL << 2) | (1ULL << 3) | (1ULL << 4) | (1ULL << 5) | (1ULL << 6);
	
	ft_memcpy(&dbl, &bigint, 8);
	setbuf(stdout, NULL);
	setlocale(LC_ALL, "en_US.UTF-8");

	ft_putstr("\nSTD\tPRINTF: '");
	len = printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\n\nMY\tPRINTF: '");
	len = ft_printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\n");
	//ft_printf(FMT);
	return (0);
}

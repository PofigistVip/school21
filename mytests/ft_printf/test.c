#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "ft_printf.h"

#define FMT "This is a simple test."

int		main(void)
{
	int		len;
	char	char1 = 'a';
	setbuf(stdout, NULL);
	ft_putstr("STD\tPRINTF: '");
	len = printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\nMY\tPRINTF: '");
	len = ft_printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\n");
	return (0);
}

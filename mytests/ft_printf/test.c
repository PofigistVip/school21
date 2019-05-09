#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "ft_printf.h"

#define FMT "%u", 42

int		main(void)
{
	int		len;
	char	char1 = 'a';
	char	*str1 = "Larlyne";
	int		int1 = 1;

	setbuf(stdout, NULL);
	ft_putstr("\nSTD\tPRINTF: '");
	len = printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\n\nMY\tPRINTF: '");
	len = ft_printf(FMT);
	ft_putstr("'(");
	ft_putnbr(len);
	ft_putstr(")\n");
	return (0);
}

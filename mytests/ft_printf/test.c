#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"

#define FMT "%5c", char1

int		main(void)
{
	char	char1 = 'a';
	ft_putstr("STD\tPRINTF: '");
	printf(FMT);
	fflush(stdout);
	ft_putstr("'\nMY\tPRINTF: '");
	ft_printf(FMT);
	ft_putstr("'\n");
	return (0);
}

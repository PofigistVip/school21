#include <unistd.h>
#include "ft_printf.h"

#if defined(__APPLE__) && defined(__MACH__)
int		ft_display_perc(int fd, t_printf_elem *el)
{
	char	symb;
	int		i;
	int		width;
	char	space;

	symb = '%';
	width = el->width;
	if (width <= 1)
	{
		write(fd, &symb, 1);
		return (1);
	}
	i = 1;
	space = ((el->flags & FT_PRINTF_ZERO) && !(el->flags & FT_PRINTF_MINUS)) ? '0' : ' ';
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, &symb, 1);
		while(i++ < width)
			write(fd, &space, 1);
		return (width);
	}
	while(i++ < width)
		write(fd, &space, 1);
	write(fd, &symb, 1);
	return (width);
}
#else
int		ft_display_perc(int fd, t_printf_elem *el)
{
	char	symb;

	(void)el;
	symb = '%';
	write(fd, &symb, 1);
	return (1);
}
#endif

#include <unistd.h>
#include "ft_printf.h"

int		ft_display_c(int fd, t_printf_elem *el)
{
	int		i;
	int		width;
	char	space;
	char	symb;

	symb = (unsigned char)el->arg->val_i;
	width = el->width;
	if (width <= 1)
	{
		write(fd, &symb, 1);
		return (1);
	}
	i = 1;
	space = ' ';
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, &symb, 1);
		while (i++ < width)
			write(fd, &space, 1);
		return (width);
	}
	while (i++ < width)
		write(fd, &space, 1);
	write(fd, &symb, 1);
	return (width);
}
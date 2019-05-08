#include "ft_printf.h"

int		ft_display_c(int fd, t_printf_elem *el)
{
	int i;
	int width;

	width = el->width;
	if (width <= 1)
	{
		write(fd, (unsigned char)el->arg->val_i, 1);
		return (1);
	}
	i = 1;
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, (unsigned char)el->arg->val_i, 1);
		while (i++ < width)
			write(fd, ' ', 1);
		return (width);
	}
	while (i++ < width)
		write(fd, ' ', 1);
	write(fd, (unsigned char)el->arg->val_i, 1);
	return (width);
}
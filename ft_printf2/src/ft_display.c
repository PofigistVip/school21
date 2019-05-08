#include "ft_printf.h"

int		ft_display_elem(int fd, t_printf_elem *el)
{
	if (el->conv_type == 0)
		return (ft_display_raw(fd, el));
	if (el->conv_type == '%')
		return (ft_display_perc(fd, el));
	if (el->conv_type == 'c')
		return (ft_display_c(fd, el));
	return (0);
}

int		ft_display(int fd, t_printf_elem *els)
{
	int length;

	length = 0;
	while (els)
	{
		length += ft_display_elem(fd, els);
		els = els->next;
	}
	return (length);
}
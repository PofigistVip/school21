
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_llist			*llist;
	t_print_elem	*el;
	int				i;
	int				count;

	llist = parse_format(format);

	i = 0;
	count = 0;
	while (i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		count += el->str_len;
		if (el->conv_type == 0)
			ft_putnchar(el->str, el->str_len);
		else if (el->conv_type == 's')
			ft_putnchar("{str}", 5);
		else if (el->conv_type == 'd' || el->conv_type == 'i')
			ft_putnchar("{int}", 5);
		else if (el->conv_type == '%')
			ft_putchar('%');
		if (el->width == 5 || el->precision == 5)
			ft_putchar('n');
		if (el->width_ref == 1 || el->precision_ref == 1)
			ft_putchar('r');
		++i;
	}
	return (count);
}
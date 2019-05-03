
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_llist			*llist;
	t_print_elem	*el;
	int				i;

	llist = parse_format(format);

	i = 0;
	while (i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		if (el->conv_type == 0)
			ft_putnchar(el->str, el->str_len);
		else if (el->conv_type == 's')
			ft_putnchar("{str}", 5);
		else if (el->conv_type == 'd' || el->conv_type == 'i')
			ft_putnchar("{int}", 5);
		++i;
	}
	return (0);
}
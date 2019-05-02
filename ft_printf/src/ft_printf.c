
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
		ft_putnchar(el->str, el->str_len);
		++i;
	}
	return (0);
}
#include <stdarg.h>
#include "ft_printf.h"

int		ft_fprintf(int fd, const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	
	if (fd < 0)
		return (0);
	elems = ft_parse(format);
	va_start(ap, format);
	args = ft_get_args(t_printf_elem *elems);
	ft_push_args(elems, args);
	va_end(ap);
	return (ft_output(fd, elems));
}

int		ft_printf(const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;

	elems = ft_parse(format, &pos);
	va_start(ap, format);
	args = ft_get_args(t_printf_elem *elems, &ap, pos);
	va_end(ap);
	ft_push_args(elems, args);
	return (ft_output(1, elems));
}
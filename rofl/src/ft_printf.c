#include <stdarg.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;

	(void)pos;
	(void)elems;
	(void)args;
	return (0);
	//elems = ft_parse((char*)format, &pos);
	va_start(ap, format);
	
	//args = ft_get_args(elems, &ap, pos);
	va_end(ap);

	//ft_push_args(elems, args);
	//return (ft_display(1, elems, args));
}
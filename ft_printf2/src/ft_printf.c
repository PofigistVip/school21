#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_fprintf(int fd, const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;
	
	if (fd < 0)
		return (0);
	elems = ft_parse((char*)format, &pos);
	va_start(ap, format);
	args = ft_get_args(elems, &ap, pos);
	ft_push_args(elems, args);
	va_end(ap);
	return (ft_display(fd, elems));
}

#define LDEBUG 0

int		ft_printf(const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;

	elems = ft_parse((char*)format, &pos);
	va_start(ap, format);
	
	args = ft_get_args(elems, &ap, pos);
	va_end(ap);
	
	ft_push_args(elems, args);
	
	return (ft_display(1, elems));
}
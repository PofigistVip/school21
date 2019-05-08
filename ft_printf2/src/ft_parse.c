#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_printf_elem	*ft_printf_elem_new(void)
{
	t_printf_elem	*el;
	
	el = (t_printf_elem*)malloc(sizeof(t_printf_elem));
	ft_bzero(el, sizeof(t_printf_elem));
	return (el);
}

void			ft_printf_elem_add(t_printf_elem **els, t_printf_elem *el)
{
	t_printf_elem	*curr;

	if (*els)
	{
		curr = *els;
		while (curr->next)
			curr = curr->next;
		curr->next = el;
	}
	else
	{
		*els = el;
	}
}

t_printf_elem	*ft_parse_rawstr(char **fmt)
{
	char			*ptr;
	t_printf_elem	*el;
	size_t			len;
	char			*raw;

	ptr = *fmt;
	while (*ptr && *ptr != '%')
		++ptr;
	el = ft_printf_elem_new();
	el->conv_type = 0;
	len = ptr - *fmt;
	raw = (char*)malloc(len + 1);
	ft_memcpy(raw, *fmt, len);
	*(raw + len) = '\0';
	el->raw_str = raw;
	*fmt = ptr;
	return (el);
}

t_printf_elem	*ft_parse(char *fmt, int *pos)
{
	t_printf_elem	*els;
	t_printf_elem	*curr;

	*pos = 1;
	while (*fmt)
	{
		if (*fmt == '%')
			curr = ft_parse_spec(&fmt, pos);
		else
			curr = ft_parse_rawstr(&fmt);
		ft_printf_elem_add(&els, curr);
	}
	return (els);
}
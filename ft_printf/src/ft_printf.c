
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		has_flag(t_print_elem *el, char flag)
{
	return (el->flags & flag);
}

void	printf_debug_print(t_print_elem *el)
{
	if (el->conv_type == 0)
		ft_putnchar(el->str, el->str_len);
	else
	{
		ft_putchar('{');
		if (has_flag(el, 1))
			ft_putchar('#');
		if (has_flag(el, 2))
			ft_putchar('0');
		if (has_flag(el, 4))
			ft_putchar('-');
		if (has_flag(el, 8))
			ft_putchar(' ');
		if (has_flag(el, 16))
			ft_putchar('+');
		if (has_flag(el, 32))
			ft_putchar('\'');
		if (has_flag(el, 64))
			ft_putchar('I');
		if (el->flags != 0)
			ft_putchar(':');
		if (el->conv_type == 's')
			ft_putnchar("str", 3);
		else if (el->conv_type == 'd' || el->conv_type == 'i')
			ft_putnchar("int", 3);
		else if (el->conv_type == 'c')
			ft_putnchar("char", 4);
		ft_putchar('(');
		ft_putnbr(el->pos);
		ft_putchar(el->length_mod);
		ft_putchar(')');
		ft_putchar(':');
		if (el->width_ref != 0)
		{
			ft_putchar('r');
			ft_putnbr(el->width_ref);
		}
		else
			ft_putnbr(el->width);
		ft_putchar('.');
		if (el->precision_ref != 0)
		{
			ft_putchar('r');
			ft_putnbr(el->precision_ref);
		}
		else
			ft_putnbr(el->precision);
		ft_putchar('}');
	}
	
	
}

void	push_args(t_llist *llist, va_list *ap)
{
	int		curr_pos;
	int		i;
	char	was_pos;
	t_print_elem	*el;

	//curr_pos = 1;
	//while (1)
	//{
		i = 0;
		was_pos = 0;
		while (i < llist->count)
		{
			el = (t_print_elem*)ft_llist_get(llist, i);
			if (el->conv_type == 'c')
				el->ptr = va_arg(*ap, unsigned);
			++i;
		}
		//if (!was_pos)
		//	break ;
	//}
}

void	printf_print(t_print_elem *el)
{
	if (el->conv_type == 'c')
		ft_putchar(*((char*)el->ptr));
	else
		ft_putnchar(el->str, el->str_len);
	
}

int		ft_printf_output(t_llist *llist)
{
	t_print_elem	*el;
	int				i;
	int				count;

	i = 0;
	count = 0;
	while (i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		printf_print(el);
		//printf_debug_print(el);
		++i;
		count += el->str_len;
	}
	return (count);
}

int		ft_printf(const char *format, ...)
{
	t_llist			*llist;
	va_list			ap;

	llist = parse_format(format);
	va_start(ap, format);
	push_args(llist, &ap);
	//ft_tostring(llist);
	va_end(ap);
	return (ft_printf_output(llist));
}
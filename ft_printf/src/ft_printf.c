
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

t_print_arg	*arg_new(void)
{
	t_print_arg	*arg;

	arg = (t_print_arg*)malloc(sizeof(t_print_arg));
	ft_bzero(arg, sizeof(t_print_arg));
	return (arg);
}

t_llist	*push_args(t_llist *llist, va_list *ap)
{
	t_llist	*args;
	int		curr_pos;
	int		i;
	char	was_pos;
	t_print_elem	*el;
	t_print_arg		*arg;

	args = ft_llist_create(sizeof(t_print_arg));
	curr_pos = 1;
	while (1)
	{
		i = -1;
		was_pos = 0;
		while (++i < llist->count)
		{
			el = (t_print_elem*)ft_llist_get(llist, i);
			if (el->conv_type == 0)
				continue ;
			if (el->pos == curr_pos || el->precision_ref == curr_pos
				|| el->width_ref == curr_pos)
			{
				was_pos = 1;
				arg = arg_new();
				if (el->width_ref == curr_pos || el->precision_ref == curr_pos)
					arg->val_i = va_arg(*ap, int);
				else if (el->conv_type == 'c' || el->conv_type == 'd'
				|| el->conv_type == 'i')
					arg->val_i = va_arg(*ap, int);
				else if (el->conv_type == 'o' || el->conv_type == 'u'
					|| el->conv_type == 'x' || el->conv_type == 'X')
					arg->val_i = va_arg(*ap, int);
				else if (el->conv_type == 'e' || el->conv_type == 'E'
					|| el->conv_type == 'f' || el->conv_type == 'F'
					|| el->conv_type == 'g' || el->conv_type == 'G'
					|| el->conv_type == 'a' || el->conv_type == 'A')
					arg->val_d = va_arg(*ap, double);
				else if (el->conv_type == 's')
					arg->ptr = (void*)va_arg(*ap, char*);
				else if (el->conv_type == 'p')
					arg->ptr = va_arg(*ap, void*);
				ft_llist_add(args, arg);
				break ;
			}
		}
		if (!was_pos)
			break ;
		++curr_pos;
	}
	return (args);
}

t_print_arg	*get_arg(t_llist *args, int pos)
{
	t_print_arg	*arg;

	if (args->count - 1 < pos || pos < 0)
		return (arg_new());
	return ((t_print_arg*)ft_llist_get(args, pos));
}

void	ft_tostrint_str(t_print_elem *el, t_print_arg *arg)
{
	size_t	len;
	size_t	width;

	len = ft_strlen((const char*)arg->ptr);
	if (el->precision != -1 && len > el->precision)
		len = el->precision;
	width = len;
	if (el->width != -1 && el->width > width)
		width = el->width;
	el->str = ft_strnew(width - 1);
	if (has_flag(el, 4))
	{
		ft_memcpy(el->str, arg->ptr, len);
		ft_memset(el->str + len, ' ', width - len);
	}
	else
	{
		ft_memset(el->str, ' ', width - len);
		ft_memcpy(el->str + (width - len), arg->ptr, len);
	}
	el->str_len = width;
}

void	ft_tostring(t_llist *llist, t_llist *args)
{
	t_print_elem	*el;
	t_print_arg		*arg;
	int				i;

	i = -1;
	while (++i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		if (el->conv_type == 0)
			continue ;
		if (el->conv_type == '%')
		{
			el->str_len = 1;
			el->str = ft_strnew(0);
			*(el->str) = '%';
			continue ;
		}
		if (el->precision_ref != 0)
			el->precision = get_arg(args, el->precision_ref - 1)->val_i;
		if (el->width_ref != 0)
			el->width = get_arg(args, el->width_ref - 1)->val_i;
		arg = get_arg(args, el->pos - 1);
		if (el->conv_type == 's')
			ft_tostrint_str(el, arg);
	}
}

void	printf_print(t_print_elem *el)
{
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
	t_llist			*args;
	va_list			ap;

	llist = parse_format(format);
	va_start(ap, format);
	args = push_args(llist, &ap);
	ft_tostring(llist, args);
	va_end(ap);
	return (ft_printf_output(llist));
}

#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include "libft.h"
#include "ft_printf.h"

int		has_flag(t_print_elem *el, char flag)
{
	return (el->flags & flag);
}

void	printf_debug_print(t_print_elem *el)
{
	if (el->conv_type == 0)
		ft_lstr_put(el->str);
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
		{
			ft_putnchar("str", 3);
			ft_putnbr(el->str->length);
		}
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

void	ft_tostring_str(t_print_elem *el, t_print_arg *arg)
{
	int		len;
	int		width;

	if (arg->ptr == NULL)
		arg->ptr = "(null)";
	len = ft_strlen((const char*)arg->ptr);
	if (el->precision != -1 && len > el->precision)
		len = el->precision;
	width = len;
	if (el->width != -1 && el->width > width)
		width = el->width;
	ft_lstr_destroy(&(el->str));
	el->str = ft_lstr_new(' ', width);
	if (has_flag(el, 4))
		ft_lstr_place_sn(el->str, arg->ptr, len, 0);
	else
		ft_lstr_place_sn(el->str, arg->ptr, len, width - len);
}

void	ft_tostring_int(t_print_elem *el, t_print_arg *arg)
{
	long long int	val;
	char			*num;
	t_lstr			*prefix;
	t_lstr			*number;

	val = arg->val_i;
	if (val == 0 && el->precision == 0)
	{
		prefix = ft_lstr_new_empty();
		number = ft_lstr_new_empty();
	}
	else
	{
		num = ft_llitoa(val);
		ft_get_di_prefix(el, num, &prefix, &number);
	}
	ft_get_diuoxX(el, prefix, number);
}

void	ft_toupperX(char *c)
{
	*c = ft_toupper(*c);
}

void	ft_tostring_ubase(t_print_elem *el, t_print_arg *arg)
{
	unsigned long long int	val;
	char		*num;
	int base;
	t_lstr			*prefix;
	t_lstr			*number;

	base = 10;
	if (el->conv_type == 'o' || el->conv_type == 'O')
		base = 8;
	else if (el->conv_type == 'x' || el->conv_type == 'X')
		base = 16;
	val = arg->val_ui;
	if (val == 0 && el->precision == 0)
	{
		prefix = ft_lstr_new_empty();
		if (el->conv_type == 'o' && has_flag(el, 1))
			number = ft_lstr_new('0', 1);
		else
			number = ft_lstr_new_empty();
	}
	else
	{
		num = ft_uitoa_base(val, base);
		ft_get_uoxX_prefix(el, num, &prefix, &number);
	}
	ft_get_diuoxX(el, prefix, number);
	if (el->conv_type == 'X')
		ft_striter(el->str->str, &ft_toupperX);
}

void	ft_tostring(t_llist *llist, t_llist *args)
{
	t_print_elem	*el;
	t_print_arg		*arg;
	size_t			i;

	i = -1;
	while (++i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		if (el->conv_type == 0)
			continue ;
		if (el->precision_ref != 0)
			el->precision = get_arg(args, el->precision_ref - 1)->val_i;
		if (el->width_ref != 0)
			el->width = get_arg(args, el->width_ref - 1)->val_i;
		if (el->conv_type == '%')
		{
			ft_lstr_destroy(&(el->str));
			if (el->width > 1)
			{
				el->str = ft_lstr_new(' ', el->width);
				if (has_flag(el, 4))
					el->str->str[0] = '%';
				else
					el->str->str[el->str->length - 1] = '%';
			}	
			else
				el->str = ft_lstr_new('%', 1);
			continue ;
		}
		arg = get_arg(args, el->pos - 1);
		if (el->conv_type == 'p')
		{
			arg->val_ui = (size_t)arg->ptr;
			el->conv_type = 'x';
			el->flags |= 1;
		}
		if (el->conv_type == 's')
			ft_tostring_str(el, arg);
		else if (el->conv_type == 'c')
		{
			ft_lstr_destroy(&(el->str));
			el->str = ft_lstr_new(' ', (el->width > 0) ? el->width : 1);
			ft_lstr_place_c(el->str, (unsigned char)arg->val_i, 1,
				has_flag(el, 4) ? 0 : el->str->length - 1);
		}
		else if (el->conv_type == 'd' || el->conv_type == 'i' || el->conv_type == 'D')
			ft_tostring_int(el, arg);
		else if (el->conv_type == 'o' || el->conv_type == 'u' ||
				el->conv_type == 'x' || el->conv_type == 'X' ||
				el->conv_type == 'U' || el->conv_type == 'O')
			ft_tostring_ubase(el, arg);
	}
}

void	printf_print(t_print_elem *el)
{
	ft_lstr_put(el->str);
}

int		ft_printf_output(t_llist *llist)
{
	t_print_elem	*el;
	size_t			i;
	int				count;

	i = 0;
	count = 0;
	while (i < llist->count)
	{
		el = (t_print_elem*)ft_llist_get(llist, i);
		printf_print(el);
		//printf_debug_print(el);
		++i;
		count += el->str->length;
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

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

t_print_arg	*arg_new(void)
{
	t_print_arg	*arg;

	arg = (t_print_arg*)malloc(sizeof(t_print_arg));
	ft_bzero(arg, sizeof(t_print_arg));
	return (arg);
}


void	push_arg(t_print_elem *el, t_print_arg *arg, va_list *ap)
{
	if (el->conv_type == 'c')
		arg->val_i = va_arg(*ap, int);
	else if(el->conv_type == 's')
		arg->ptr  = va_arg(*ap, char*);
	else if (el->conv_type == 'd' || el->conv_type == 'i')
	{
		if (el->length_mod == 'H')
			arg->val_i = va_arg(*ap, int);
		else if (el->length_mod == 'h')
			arg->val_i = va_arg(*ap, int);
		else if (el->length_mod == 'l')
			arg->val_i = va_arg(*ap, long int);
		else if (el->length_mod == 'M')
			arg->val_i = va_arg(*ap, long long int);
		else if (el->length_mod == 'j')
			arg->val_i = va_arg(*ap, intmax_t);
		else if (el->length_mod == 'z')
			arg->val_i = va_arg(*ap, ssize_t);
		else
			arg->val_i = va_arg(*ap, int);
	}
	else if (el->conv_type == 'o' || el->conv_type == 'u' ||
			el->conv_type == 'x' || el->conv_type == 'X')
	{
		if (el->length_mod == 'H')
			arg->val_ui = va_arg(*ap, unsigned int);
		else if (el->length_mod == 'h')
			arg->val_ui = va_arg(*ap, unsigned int);
		else if (el->length_mod == 'l')
			arg->val_ui = va_arg(*ap, unsigned long int);
		else if (el->length_mod == 'M')
			arg->val_ui = va_arg(*ap, unsigned long long int);
		else if (el->length_mod == 'j')
			arg->val_ui = va_arg(*ap, uintmax_t);
		else if (el->length_mod == 'z')
			arg->val_ui = va_arg(*ap, size_t);
		else
			arg->val_ui = va_arg(*ap, unsigned int);
	}
}

t_llist	*push_args(t_llist *llist, va_list *ap)
{
	t_llist	*args;
	int		curr_pos;
	size_t	i;
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
				else
					push_arg(el, arg, ap);
				
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
	if ((int)args->count - 1 < pos || pos < 0)
		return (arg_new());
	return ((t_print_arg*)ft_llist_get(args, pos));
}

void	ft_tostring_str(t_print_elem *el, t_print_arg *arg)
{
	int		len;
	int		width;

	if (arg->ptr == NULL)
	{
		ft_lstr_insert_s(el->str, "(null)", 0);
		return ;
	}
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
	char		*num;

	val = arg->val_i;
	num = ft_itoa(val);
	ft_lstr_destroy(&(el->str));
	el->str = ft_lstr_new_raw(num);
	if (val >= 0)
	{
		if (has_flag(el, 16))
			ft_lstr_insert_c(el->str, '+', 1, 0);
		else if (has_flag(el, 8))
			ft_lstr_insert_c(el->str, ' ', 1, 0);
	}
	if (el->width > el->str->length)
	{
		if (has_flag(el, 4))
			ft_lstr_insert_c(el->str, ' ', el->width - el->str->length,
				el->str->length);
		else
		{
			if (has_flag(el, 2))
				ft_lstr_insert_c(el->str, '0', el->width - el->str->length,
					has_flag(el, 16) || has_flag(el, 8) ? 1 : 0);
			else
				ft_lstr_insert_c(el->str, ' ', el->width - el->str->length, 0);
			
		}
	}
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

	base = 10;
	if (el->conv_type == 'o')
		base = 8;
	else if (el->conv_type == 'x' || el->conv_type == 'X')
		base = 16;
	val = arg->val_ui;
	num = ft_uitoa_base(val, base);
	ft_lstr_destroy(&(el->str));
	el->str = ft_lstr_new_raw(num);
	if (has_flag(el, 1))
	{
		if (el->conv_type == 'x' || el->conv_type == 'X')
			ft_lstr_insert_s(el->str, "0x", 0);
		else if (el->conv_type == 'o')
			ft_lstr_insert_s(el->str, "0", 0);
	}
	if (el->width > el->str->length)
	{
		if (has_flag(el, 4))
			ft_lstr_insert_c(el->str, ' ', el->width - el->str->length,
				el->str->length);
		else
		{
			if (!has_flag(el, 2))
				ft_lstr_insert_c(el->str, ' ', el->width - el->str->length, 0);
			else
			{
				if (!has_flag(el, 1) || el->conv_type == 'u')
					ft_lstr_insert_c(el->str, '0', el->width - el->str->length, 0);
				else if (el->conv_type == 'o')
					ft_lstr_insert_c(el->str, '0', el->width - el->str->length, 0);
				else
					ft_lstr_insert_c(el->str, '0', el->width - el->str->length, 2);
			}
			
		}
	}
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
		if (el->conv_type == 's')
			ft_tostring_str(el, arg);
		else if (el->conv_type == 'c')
		{
			ft_lstr_destroy(&(el->str));
			el->str = ft_lstr_new(' ', (el->width > 0) ? el->width : 1);
			ft_lstr_place_c(el->str, (unsigned char)arg->val_i, 1,
				has_flag(el, 4) ? 0 : el->str->length - 1);
		}
			
		else if (el->conv_type == 'd' || el->conv_type == 'i')
			ft_tostring_int(el, arg);
		else if (el->conv_type == 'o' || el->conv_type == 'u' ||
				el->conv_type == 'x' || el->conv_type == 'X')
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
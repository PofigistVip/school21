#include <stdarg.h>
#include <wchar.h>
#include <stdlib.h>
#include <inttypes.h>
#include "libft.h"
#include "ft_printf.h"

t_printf_arg	*ft_arg_new(void)
{
	t_printf_arg	*arg;

	arg = (t_printf_arg*)malloc(sizeof(t_printf_arg));
	ft_bzero(arg, sizeof(t_printf_arg));
	return (arg);
}

void			ft_arg_add(t_printf_arg **args, t_printf_arg *arg)
{
	t_printf_arg	*curr;

	if (*args)
	{
		curr = *args;
		while (curr->next)
			curr = curr->next;
		curr->next = arg;
	}
	else
	{
		*args = arg;
	}
}

void			ft_get_arg(char conv, char length, va_list *ap,
					t_printf_arg* arg)
{
	if (conv == 'x' || conv == 'X' || conv == 'o' || conv == 'u')
	{
		if (length == 'H')
			arg->val_ui = (unsigned char)va_arg(*ap, unsigned int);
		else if (length == 'h')
			arg->val_ui = (unsigned short int)va_arg(*ap, unsigned int);
		else if (length == 'l')
			arg->val_ui = va_arg(*ap, unsigned long int);
		else if (length == 'M')
			arg->val_ui = va_arg(*ap, unsigned long long int);
		else if (length == 'j')
			arg->val_ui = va_arg(*ap, uintmax_t);
		else if (length == 'z')
			arg->val_ui = va_arg(*ap, size_t);
		else
			arg->val_ui = va_arg(*ap, unsigned int);
	}
	else if (conv == 's' || conv == 'S')
		arg->ptr = va_arg(*ap, void*);
	else if (conv == 'c' && length != 'l')
		arg->val_i = va_arg(*ap, int);
	else if (conv == 'd' || conv == 'i')
	{
		if (length == 'H')
			arg->val_i = (signed char)va_arg(*ap, signed int);
		else if (length == 'h')
			arg->val_i = (signed short int)va_arg(*ap, signed int);
		else if (length == 'l')
			arg->val_i = va_arg(*ap, signed long int);
		else if (length == 'M')
			arg->val_i = va_arg(*ap, signed long long int);
		else if (length == 'j')
			arg->val_i = va_arg(*ap, intmax_t);
		else if (length == 'z')
			arg->val_i = va_arg(*ap, ssize_t);
		else
			arg->val_i = va_arg(*ap, signed int);
	}
	else if (conv == 'U')
		arg->val_ui = va_arg(*ap, unsigned long int);
	else if (conv == 'p')
		arg->val_ui = (unsigned long int)va_arg(*ap, void*);
	else if (conv == 'O')
		arg->val_ui = va_arg(*ap, unsigned long int);
	else if (conv == 'D')
		arg->val_i = va_arg(*ap, signed long int);
	else if (conv == 'C' || (conv == 'c' && length == 'l'))
		arg->val_wc = va_arg(*ap, wchar_t);
	else if (conv == 'f' || conv == 'F')
		arg->val_d = va_arg(*ap, double);
}

t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos)
{
	t_printf_elem	*el;
	int				pos;
	t_printf_arg	*args;
	t_printf_arg	*arg;

	args = 0;
	pos = 1;
	
	while (pos < end_pos)
	{
		el = els;
		arg = ft_arg_new();
		while (el)
		{
			if (el->precision_pos == pos || el->width_pos == pos)
			{
				arg->val_i = va_arg(*ap, int);
				break ;
			}
			else if (el->pos == pos)
			{
				ft_get_arg(el->conv_type, el->length_mod, ap, arg);
				break ;
			}
			el = el->next;
		}
		
		ft_arg_add(&args, arg);
		++pos;
	}
	return (args);
}
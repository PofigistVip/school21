#include <stdarg.h>
#include <wchar.h>
#include "libft.h"
#include "ft_printf.h"

void			ft_get_arg(char conv, char length, va_list *ap,
					t_printf_arg* arg)
{
	if (conv == 'c')
	{
		if (length == 'l')
			arg->val_wc = va_arg(*ap, wchar_t);
		else
			arg->val_i = va_arg(*ap, int);
	}
}

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

t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos)
{
	t_printf_elem	*el;
	int				pos;
	t_printf_arg	*args;
	t_printf_arg	*arg;

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
				ft_get_arg(el->conv_type, el->length_mod, arg);
				break ;
			}
			el = el->next;
		}
		ft_arg_add(&args, arg);
		++pos;
	}
}
#include "libft.h"
#include "ft_printf.h"

void	ft_basic_params(t_printf_elem *el, char conv_type)
{
	if (conv_type == 'x' || conv_type == 'X' || conv_type == 'o'
		|| conv_type == 'O' || conv_type == 'd' || conv_type == 'D'
		|| conv_type == 'i' || conv_type == 'u' || conv_type == 'U'
		|| conv_type == 'p')
	{
		if (el->precision_seted == 0)
			el->precision = 1;
	}
}

void	ft_push_arg(int pos, t_printf_elem *el, t_printf_arg *arg)
{
	if (el->width_pos == pos && el->width_seted == 0)
	{
		el->width = arg->val_i;
		if (el->width < 0)
		{
			el->width = -el->width;
			el->flags |= FT_PRINTF_MINUS;
		}
		el->width_seted = 1;
	}
	if (el->precision_pos == pos)
	{
		el->precision = arg->val_i;
		el->precision_seted = 1;
	}
	if (el->pos == pos)
		el->arg = arg;
}

void	ft_push_args(t_printf_elem *els, t_printf_arg *args)
{
	t_printf_elem	*el;
	int				pos;

	pos = 1;
	while (args)
	{
		el = els;
		while (el)
		{
			if (el->conv_type)
			{
				ft_basic_params(el, el->conv_type);
				ft_push_arg(pos, el, args);
			}
			el = el->next;
		}
		args = args->next;
		++pos;
	}
}
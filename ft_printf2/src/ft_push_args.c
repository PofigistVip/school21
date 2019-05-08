#include "libft.h"
#include "ft_printf.h"

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
				if (el->width_pos == pos)
					el->width = args->val_i;
				if (el->precision_pos == pos)
					el->precision = args->val_i;
				if (el->pos == pos)
					el->arg = args;
			}
			el = el->next;
		}
		args = args->next;
		++pos;
	}
}
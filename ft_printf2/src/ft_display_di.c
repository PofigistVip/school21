#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_di_prefix(t_printf_elem *el)
{
	if (el->arg->val_i < 0 || (el->flags & FT_PRINTF_PLUS) ||
		(el->flags & FT_PRINTF_SPACE))
		return (1);
	return (0);
}

void	ft_display_di_inner(t_printf_elem *el, t_lstr *num, int prefix)
{
	if (el->precision > num->length - prefix)
		ft_lstr_insert_c(num, '0',
			el->precision - num->length + prefix, prefix);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO && !(el->precision_seted &&
			el->width_seted))
			ft_lstr_insert_c(num, '0', el->width - num->length, prefix);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
}

int		ft_display_di(int fd, t_printf_elem *el)
{
	signed long long int	val;
	int						prefix;
	t_lstr					*num;

	val = el->arg->val_i;
	if (val == 0 && el->precision == 0)
		return (ft_putcharn_fd(fd, ' ', el->width));
	num = ft_lstr_new_raw(ft_llitoa(val));
	if (val >= 0)
	{
		if (el->flags & FT_PRINTF_PLUS)
			ft_lstr_insert_c(num, '+', 1, 0);
		else if (el->flags & FT_PRINTF_SPACE)
			ft_lstr_insert_c(num, ' ', 1, 0);
	}
	prefix = ft_di_prefix(el);
	ft_display_di_inner(el, num, prefix);
	ft_lstr_put_fd(num, fd);
	val = num->length;
	ft_lstr_destroy(&num);
	return (val);
}
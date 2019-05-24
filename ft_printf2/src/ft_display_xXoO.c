#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_x(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if (val == 0 && el->precision == 0)
		return (ft_putcharn_fd(fd, ' ', el->width));
	num = ft_lstr_new_raw(ft_uitoa_base(val, 16, 0));
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (el->flags & FT_PRINTF_SHARP && val != 0)
		ft_lstr_insert_s(num, "0x", 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO)
			ft_lstr_insert_c(num, '0', el->width - num->length,
				(el->flags & FT_PRINTF_SHARP) ? 2 : 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}

int		ft_display_X(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if (val == 0 && el->precision == 0)
		return (ft_putcharn_fd(fd, ' ', el->width));
	num = ft_lstr_new_raw(ft_uitoa_base(val, 16, 1));
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (el->flags & FT_PRINTF_SHARP && val != 0)
		ft_lstr_insert_s(num, "0X", 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO)
			ft_lstr_insert_c(num, '0', el->width - num->length,
				(el->flags & FT_PRINTF_SHARP) ? 2 : 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}

int		ft_display_o(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if (val != 0 || el->precision > 0)
		num = ft_lstr_new_raw(ft_uitoa_base(val, 8, 0));
	else
		num = ft_lstr_new_empty();
	if (el->flags & FT_PRINTF_SHARP)
		ft_lstr_insert_c(num, '0', 1, 0);
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO)
			ft_lstr_insert_c(num, '0', el->width - num->length,
				(el->flags & FT_PRINTF_SHARP) ? 1 : 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}

#if defined(__APPLE__) && defined(__MACH__)
int		ft_display_O(int fd, t_printf_elem *el)
{
	return (ft_display_o(fd, el));
}
#else
int		ft_display_O(int fd, t_printf_elem *el)
{
	(void)el;
	write(fd, "%O", 2);
	return (2);
}
#endif
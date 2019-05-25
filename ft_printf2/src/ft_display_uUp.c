#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_u(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if (val == 0 && el->precision == 0)
		return (ft_putcharn_fd(fd, ' ', el->width));
	num = ft_lstr_new_raw(ft_uitoa_base(val, 10, 0));
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO && !el->precision_seted)
			ft_lstr_insert_c(num, '0', el->width - num->length, 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}

#if defined(__APPLE__) && defined(__MACH__)
int		ft_display_U(int fd, t_printf_elem *el)
{
	return (ft_display_u(fd, el));
}
#else
int		ft_display_U(int fd, t_printf_elem *el)
{
	return (ft_display_Unknown(fd, el));
}
#endif

#if defined(__linux__) || defined(_WIN32)
int		ft_display_zero_ptr(int fd, t_printf_elem *el)
{
	int		max;

	max = 5;
	if (el->width > max)
		max = el->width;
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, "(nil)", 5);
		ft_putcharn_fd(fd, ' ', max - 5);
	}
	else
	{
		ft_putcharn_fd(fd, ' ', max - 5);
		write(fd, "(nil)", 5);
	}
	return (max);
}
#endif

#if defined(__APPLE__) && defined(__MACH__)
int		ft_display_p(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;
	
	val = el->arg->val_ui;
	if (val != 0 || el->precision > 0)
		num = ft_lstr_new_raw(ft_uitoa_base(val, 16, 0));
	else
		num = ft_lstr_new_empty();
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	ft_lstr_insert_s(num, "0x", 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO)
			ft_lstr_insert_c(num, '0', el->width - num->length, 2);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}
#else
int		ft_display_p(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;
	
	val = el->arg->val_ui;
	if (val == 0)
		return (ft_display_zero_ptr(fd, el));
	num = ft_lstr_new_raw(ft_uitoa_base(val, 16, 0));
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	ft_lstr_insert_s(num, "0x", 0);
	//Обработка FT_PRINTF_SPACE и FT_PINRF_PLUS - возможно только linux
	if (el->flags & FT_PRINTF_PLUS)
		ft_lstr_insert_c(num, '+', 1, 0);
	else if (el->flags & FT_PRINTF_SPACE)
		ft_lstr_insert_c(num, ' ', 1, 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO)
			ft_lstr_insert_c(num, '0', el->width - num->length, 2);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	

	ft_lstr_put_fd(num, fd);
	val = (unsigned long long int)num->length;
	ft_lstr_destroy(&num);
	return (val);
}
#endif
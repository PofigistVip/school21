/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_xXoO.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:56:17 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:56:19 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (num && el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (num && el->flags & FT_PRINTF_SHARP && val != 0)
		ft_lstr_insert_s(num, "0x", 0);
	if (num && el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else if (num)
	{
		if (el->flags & FT_PRINTF_ZERO && !el->precision_seted)
			ft_lstr_insert_c(num, '0', el->width - num->length,
				(el->flags & FT_PRINTF_SHARP && val != 0) ? 2 : 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (num) ? (unsigned long long int)num->length : -1;
	ft_lstr_destroy(&num);
	return (val);
}

int		ft_display_big_x(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if (val == 0 && el->precision == 0)
		return (ft_putcharn_fd(fd, ' ', el->width));
	num = ft_lstr_new_raw(ft_uitoa_base(val, 16, 1));
	if (num && el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (num && el->flags & FT_PRINTF_SHARP && val != 0)
		ft_lstr_insert_s(num, "0X", 0);
	if (num && el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else if (num)
	{
		if (el->flags & FT_PRINTF_ZERO && !el->precision_seted)
			ft_lstr_insert_c(num, '0', el->width - num->length,
				(el->flags & FT_PRINTF_SHARP && val != 0) ? 2 : 0);
		else
			ft_lstr_insert_c(num, ' ', el->width - num->length, 0);
	}
	ft_lstr_put_fd(num, fd);
	val = (num) ? (unsigned long long int)num->length : -1;
	ft_lstr_destroy(&num);
	return (val);
}

int		ft_display_o(int fd, t_printf_elem *el)
{
	unsigned long long int	val;
	t_lstr					*num;

	val = el->arg->val_ui;
	if ((num = (val != 0) ? ft_lstr_new_raw(ft_uitoa_base(val, 8, 0)) :
		ft_lstr_new_empty()) == NULL)
		return (-1);
	if (el->flags & FT_PRINTF_SHARP)
		ft_lstr_insert_c(num, '0', 1, 0);
	if (el->precision > num->length)
		ft_lstr_insert_c(num, '0', el->precision - num->length, 0);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(num, ' ', el->width - num->length, num->length);
	else
	{
		if (el->flags & FT_PRINTF_ZERO && !el->precision_seted)
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

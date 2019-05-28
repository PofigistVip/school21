/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_f_big_f.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:07:32 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 14:07:33 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "ft_printf.h"

void			ft_get_number(long double val, t_printf_elem *el,
			t_double_keeper *keeper)
{
	if (val != val)
	{
		keeper->int_part = ft_lstr_new_copy((el->conv_type == 'F') ?
			"NAN" : "nan");
		keeper->dec_part = ft_lstr_new_empty();
		el->precision = 0;
		el->flags = el->flags & (!FT_PRINTF_ZERO);
		return ;
	}
	if (keeper->mantissa - 16383 == 16384)
	{
		keeper->int_part = ft_lstr_new_copy((el->conv_type == 'F') ?
			"INF" : "inf");
		keeper->dec_part = ft_lstr_new_empty();
		el->precision = 0;
		el->flags = el->flags & (!FT_PRINTF_ZERO);
		return ;
	}
	if (keeper->mantissa == 0)
		ft_f_get_subnormal(keeper->fraction, &(keeper->int_part),
			&(keeper->dec_part));
	else
		ft_f_get_normal(keeper->mantissa - 16383, keeper->fraction,
			&(keeper->int_part), &(keeper->dec_part));
}

void			ft_prepare_nums_inner(t_printf_elem *el, t_lstr *int_part,
					t_lstr *dec_part, int length)
{
	if (el->precision == 0)
	{
		ft_lstr_resize(dec_part, 0);
		dec_part->length = 0;
		ft_f_round(int_part, dec_part, 0);
		if (el->flags & FT_PRINTF_SHARP)
			ft_lstr_insert_c(dec_part, '.', 1, 0);
	}
	else
	{
		if (el->precision >= dec_part->length)
			ft_lstr_insert_c(dec_part, '0', el->precision - dec_part->length,
				dec_part->length);
		else
			ft_f_round(int_part, dec_part, el->precision);
		ft_lstr_insert_c(dec_part, '.', 1, 0);
	}
	if (el->width > length && (el->flags & FT_PRINTF_MINUS))
		ft_lstr_insert_c(dec_part, ' ', el->width - length, dec_part->length);
}

void			ft_prepare_nums(t_printf_elem *el, t_double_keeper *keeper)
{
	int		length;
	t_lstr	*int_part;
	t_lstr	*dec_part;

	int_part = keeper->int_part;
	dec_part = keeper->dec_part;
	if (keeper->sign)
		ft_lstr_insert_c(int_part, '-', 1, 0);
	else if (el->flags & (FT_PRINTF_PLUS | FT_PRINTF_SPACE))
		ft_lstr_insert_c(int_part, (el->flags & FT_PRINTF_PLUS) ? '+' : ' ',
		1, 0);
	length = int_part->length + el->precision + ((el->precision ||
		el->flags & FT_PRINTF_SHARP) ? 1 : 0);
	if (el->width > length && !(el->flags & FT_PRINTF_MINUS))
		ft_lstr_insert_c(int_part, (el->flags & FT_PRINTF_ZERO) ? '0' : ' ',
			el->width - length, ((el->flags & FT_PRINTF_ZERO) && (keeper->sign
			|| (el->flags & (FT_PRINTF_PLUS | FT_PRINTF_SPACE)) ? 1 : 0)));
	ft_prepare_nums_inner(el, int_part, dec_part, length);
}

int				ft_show_double(int fd, t_double_keeper *keeper)
{
	int		length;
	t_lstr	*int_part;
	t_lstr	*dec_part;

	int_part = keeper->int_part;
	dec_part = keeper->dec_part;
	ft_lstr_put_fd(int_part, fd);
	ft_lstr_put_fd(dec_part, fd);
	if (int_part && dec_part)
		length = int_part->length + dec_part->length;
	else
		length = -1;
	if (int_part)
		ft_lstr_destroy(&int_part);
	if (dec_part)
		ft_lstr_destroy(&dec_part);
	free(keeper);
	return (length);
}

int				ft_display_f_big_f(int fd, t_printf_elem *el)
{
	t_double_keeper	*keeper;

	if ((keeper = (t_double_keeper*)malloc(sizeof(t_double_keeper))) == NULL)
		return (-1);
	ft_get_sign_mantissa_fraction(el->arg->val_d, keeper);
	keeper->int_part = 0;
	keeper->dec_part = 0;
	ft_get_number(el->arg->val_d, el, keeper);
	ft_prepare_nums(el, keeper);
	return (ft_show_double(fd, keeper));
}

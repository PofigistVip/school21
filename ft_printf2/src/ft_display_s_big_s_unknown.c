/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_sS.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:44:18 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:44:22 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_s(int fd, t_printf_elem *el)
{
	int		length;
	int		len;
	char	*str;
	char	space;

	length = 0;
	str = (el->arg->ptr == 0) ? "(null)" : (char*)el->arg->ptr;
	len = (int)ft_strlen(str);
	if (el->precision_seted && el->precision >= 0 && el->precision < len)
		len = el->precision;
	space = ((el->flags & FT_PRINTF_ZERO) && !(el->flags & FT_PRINTF_MINUS))
		? '0' : ' ';
	if (el->flags & FT_PRINTF_MINUS)
	{
		length += ft_putstrn_fd(fd, str, len);
		return (length + ft_putcharn_fd(fd, space, el->width - len));
	}
	else
	{
		length += ft_putcharn_fd(fd, space, el->width - len);
		return (length + ft_putstrn_fd(fd, str, len));
	}
}

int		ft_display_big_s(int fd, t_printf_elem *el)
{
	t_lstr	*lstr;
	wchar_t	*wstr;
	int		length;

	if (el->arg->ptr == 0)
		return (ft_display_s(fd, el));
	wstr = (wchar_t*)el->arg->ptr;
	lstr = ft_lstr_new_empty();
	while (*wstr && (el->precision_seted == 0 ||
			lstr->length + ft_byte_size(*wstr) <= el->precision))
		ft_putwchar(lstr, *wstr++);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, lstr->length);
	else
		ft_lstr_insert_c(lstr, (el->flags & FT_PRINTF_ZERO) ? '0' : ' ',
		el->width - lstr->length, 0);
	ft_lstr_put_fd(lstr, fd);
	length = lstr->length;
	ft_lstr_destroy(&lstr);
	return (length);
}

int		ft_display_unknown(int fd, t_printf_elem *el)
{
	int		length;
	t_lstr	*lstr;

	lstr = ft_lstr_new_empty();
	ft_lstr_insert_c(lstr, el->conv_type, 1, 0);
	if (el->width > lstr->length)
	{
		if (el->flags & FT_PRINTF_MINUS)
			ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, lstr->length);
		else
			ft_lstr_insert_c(lstr, (el->flags & FT_PRINTF_ZERO) ? '0' : ' ',
			el->width - lstr->length, 0);
	}
	length = lstr->length;
	ft_lstr_put_fd(lstr, fd);
	ft_lstr_destroy(&lstr);
	return (length);
}

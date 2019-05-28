/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:27:04 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:27:16 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_process_pos(t_printf_elem *el, int pos, va_list *ap,
			t_printf_arg *arg)
{
	if (el->precision_pos == pos || el->width_pos == pos)
		arg->val_i = va_arg(*ap, int);
	else if (el->pos == pos)
		ft_get_arg(el->conv_type, el->length_mod, ap, arg);
	else
		return (0);
	return (1);
}

int		ft_max_pos(t_printf_elem *els)
{
	int		pos;

	pos = 0;
	while (els)
	{
		if (els->pos > pos)
			pos = els->pos;
		if (els->conv_type)
		{
			if (els->width_pos > pos)
				pos = els->width_pos;
			if (els->precision_pos > pos)
				pos = els->precision_pos;
		}
		els = els->next;
	}
	return (pos);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;
	int				ok;

	if (fd < 0)
		return (0);
	ok = 1;
	elems = ft_parse((char*)format, &pos, &ok);
	if (!ok)
	{
		ft_memfree(elems, 0);
		return (-1);
	}
	va_start(ap, format);
	args = ft_get_args(elems, &ap, ft_max_pos(elems), &ok);
	va_end(ap);
	if (!ok)
	{
		ft_memfree(elems, args);
		return (-1);
	}
	ft_push_args(elems, args);
	return (ft_display(fd, elems, args));
}

int		ft_printf(const char *format, ...)
{
	t_printf_elem	*elems;
	va_list			ap;
	t_printf_arg	*args;
	int				pos;
	int				ok;

	ok = 1;
	elems = ft_parse((char*)format, &pos, &ok);
	if (!ok)
	{
		ft_memfree(elems, 0);
		return (-1);
	}
	va_start(ap, format);
	args = ft_get_args(elems, &ap, ft_max_pos(elems), &ok);
	va_end(ap);
	if (!ok)
	{
		ft_memfree(elems, args);
		return (-1);
	}
	ft_push_args(elems, args);
	return (ft_display(1, elems, args));
}

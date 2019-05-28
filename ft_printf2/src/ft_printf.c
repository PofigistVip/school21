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
	args = ft_get_args(elems, &ap, pos, &ok);
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
	args = ft_get_args(elems, &ap, pos, &ok);
	va_end(ap);
	if (!ok)
	{
		ft_memfree(elems, args);
		return (-1);
	}
	ft_push_args(elems, args);
	return (ft_display(1, elems, args));
}

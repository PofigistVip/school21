/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:23:10 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 13:23:12 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int		ft_display_elem_inner(int fd, t_printf_elem *el)
{
	if (el->conv_type == 'O')
		return (ft_display_big_o(fd, el));
	if (el->conv_type == 'D')
		return (ft_display_big_d(fd, el));
	if (el->conv_type == 'C' || el->conv_type == 'c')
		return (ft_display_big_c(fd, el));
	if (el->conv_type == 'S' || el->conv_type == 's')
		return (ft_display_big_s(fd, el));
	if (el->conv_type == 'f' || el->conv_type == 'F')
		return (ft_display_f_big_f(fd, el));
	return (ft_display_unknown(fd, el));
}

int		ft_display_elem(int fd, t_printf_elem *el)
{
	if (el->conv_type == 0)
		return (ft_display_raw(fd, el));
	if (el->conv_type == '%')
		return (ft_display_perc(fd, el));
	if (el->conv_type == 'x')
		return (ft_display_x(fd, el));
	if (el->conv_type == 'X')
		return (ft_display_big_x(fd, el));
	if (el->conv_type == 's' && el->length_mod != 'l')
		return (ft_display_s(fd, el));
	if (el->conv_type == 'c' && el->length_mod != 'l')
		return (ft_display_c(fd, el));
	if (el->conv_type == 'o')
		return (ft_display_o(fd, el));
	if (el->conv_type == 'd' || el->conv_type == 'i')
		return (ft_display_di(fd, el));
	if (el->conv_type == 'u')
		return (ft_display_u(fd, el));
	if (el->conv_type == 'U')
		return (ft_display_big_u(fd, el));
	if (el->conv_type == 'p')
		return (ft_display_p(fd, el));
	return (ft_display_elem_inner(fd, el));
}

void	ft_memfree(t_printf_elem *els, t_printf_arg *args)
{
	t_printf_elem	*el;
	t_printf_arg	*arg;

	while (els)
	{
		el = els->next;
		if (els->raw_str != 0)
			free(els->raw_str);
		free(els);
		els = el;
	}
	while (args)
	{
		arg = args->next;
		free(args);
		args = arg;
	}
}

int		ft_display(int fd, t_printf_elem *els, t_printf_arg *args)
{
	t_printf_elem	*start;
	int				length;

	start = els;
	length = 0;
	while (els)
	{
		length += ft_display_elem(fd, els);
		els = els->next;
	}
	ft_memfree(start, args);
	return (length);
}

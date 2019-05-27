/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:07:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 13:07:04 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <wchar.h>
#include <stdlib.h>
#include <inttypes.h>
#include "libft.h"
#include "ft_printf.h"

void			ft_arg_add(t_printf_arg **args, t_printf_arg *arg)
{
	t_printf_arg	*curr;

	if (*args)
	{
		curr = *args;
		while (curr->next)
			curr = curr->next;
		curr->next = arg;
	}
	else
		*args = arg;
}

void			ft_get_arg_inner_inner(char conv, char length,
					va_list *ap, t_printf_arg *arg)
{
	if (conv == 'f' || conv == 'F')
	{
		if (length == 'L')
			arg->val_d = va_arg(*ap, long double);
		else
			arg->val_d = (long double)va_arg(*ap, double);
	}
	else if (conv == 'U')
		arg->val_ui = va_arg(*ap, unsigned long int);
	else if (conv == 'p')
		arg->val_ui = (unsigned long long int)va_arg(*ap, void*);
	else if (conv == 'O')
		arg->val_ui = va_arg(*ap, unsigned long int);
	else if (conv == 'D')
		arg->val_i = va_arg(*ap, signed long int);
	else if (conv == 'C' || (conv == 'c' && length == 'l'))
		arg->val_wc = va_arg(*ap, wchar_t);
}

void			ft_get_arg_inner(char conv, char length, va_list *ap,
					t_printf_arg *arg)
{
	if (conv == 'd' || conv == 'i')
	{
		if (length == 'H')
			arg->val_i = (signed char)va_arg(*ap, signed int);
		else if (length == 'h')
			arg->val_i = (signed short int)va_arg(*ap, signed int);
		else if (length == 'l')
			arg->val_i = va_arg(*ap, signed long int);
		else if (length == 'M')
			arg->val_i = va_arg(*ap, signed long long int);
		else if (length == 'j')
			arg->val_i = va_arg(*ap, intmax_t);
		else if (length == 'z')
			arg->val_i = va_arg(*ap, ssize_t);
		else
			arg->val_i = va_arg(*ap, signed int);
	}
	else
		ft_get_arg_inner_inner(conv, length, ap, arg);
}

void			ft_get_arg(char conv, char length, va_list *ap,
					t_printf_arg *arg)
{
	if (conv == 'x' || conv == 'X' || conv == 'o' || conv == 'u')
	{
		if (length == 'H')
			arg->val_ui = (unsigned char)va_arg(*ap, unsigned int);
		else if (length == 'h')
			arg->val_ui = (unsigned short int)va_arg(*ap, unsigned int);
		else if (length == 'l')
			arg->val_ui = va_arg(*ap, unsigned long int);
		else if (length == 'M')
			arg->val_ui = va_arg(*ap, unsigned long long int);
		else if (length == 'j')
			arg->val_ui = va_arg(*ap, uintmax_t);
		else if (length == 'z')
			arg->val_ui = va_arg(*ap, size_t);
		else
			arg->val_ui = va_arg(*ap, unsigned int);
	}
	else if (conv == 's' || conv == 'S')
		arg->ptr = va_arg(*ap, void*);
	else if (conv == 'c' && length != 'l')
		arg->val_i = va_arg(*ap, int);
	else
		ft_get_arg_inner(conv, length, ap, arg);
}

t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos)
{
	int				pos;
	t_printf_arg	*args;
	t_printf_arg	*arg;

	args = 0;
	pos = 1;
	while (pos < end_pos)
	{
		arg = ft_arg_new();
		while (els)
		{
			if (els->precision_pos == pos || els->width_pos == pos)
				arg->val_i = va_arg(*ap, int);
			else if (els->pos == pos)
				ft_get_arg(els->conv_type, els->length_mod, ap, arg);
			if (els->precision_pos == pos || els->width_pos == pos ||
				els->pos == pos)
				break ;
			els = els->next;
		}
		ft_arg_add(&args, arg);
		++pos;
	}
	return (args);
}

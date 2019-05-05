/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 13:56:54 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/05 13:57:00 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <inttypes.h>
#include "libft.h"
#include "ft_printf.h"

t_print_arg	*arg_new(void)
{
	t_print_arg	*arg;

	arg = (t_print_arg*)malloc(sizeof(t_print_arg));
	ft_bzero(arg, sizeof(t_print_arg));
	return (arg);
}


void	push_arg(t_print_elem *el, t_print_arg *arg, va_list *ap)
{
	if (el->conv_type == 'c')
		arg->val_i = va_arg(*ap, int);
	else if (el->conv_type == 's')
		arg->ptr  = va_arg(*ap, char*);
	else if (el->conv_type == 'd' || el->conv_type == 'i')
	{
		if (el->length_mod == 'H')
			arg->val_i = va_arg(*ap, int);
		else if (el->length_mod == 'h')
			arg->val_i = va_arg(*ap, int);
		else if (el->length_mod == 'l')
			arg->val_i = va_arg(*ap, long int);
		else if (el->length_mod == 'M')
			arg->val_i = va_arg(*ap, long long int);
		else if (el->length_mod == 'j')
			arg->val_i = va_arg(*ap, intmax_t);
		else if (el->length_mod == 'z')
			arg->val_i = va_arg(*ap, ssize_t);
		else
			arg->val_i = va_arg(*ap, int);
	}
	else if (el->conv_type == 'o' || el->conv_type == 'u' ||
			el->conv_type == 'x' || el->conv_type == 'X')
	{
		if (el->length_mod == 'H')
			arg->val_ui = va_arg(*ap, unsigned int);
		else if (el->length_mod == 'h')
			arg->val_ui = va_arg(*ap, unsigned int);
		else if (el->length_mod == 'l')
			arg->val_ui = va_arg(*ap, unsigned long int);
		else if (el->length_mod == 'M')
			arg->val_ui = va_arg(*ap, unsigned long long int);
		else if (el->length_mod == 'j')
			arg->val_ui = va_arg(*ap, uintmax_t);
		else if (el->length_mod == 'z')
			arg->val_ui = va_arg(*ap, size_t);
		else
			arg->val_ui = va_arg(*ap, unsigned int);
	}
}

t_llist	*push_args(t_llist *llist, va_list *ap)
{
	t_llist	*args;
	int		curr_pos;
	size_t	i;
	char	was_pos;
	t_print_elem	*el;
	t_print_arg		*arg;

	args = ft_llist_create(sizeof(t_print_arg));
	curr_pos = 1;
	while (1)
	{
		i = -1;
		was_pos = 0;
		while (++i < llist->count)
		{
			el = (t_print_elem*)ft_llist_get(llist, i);
			if (el->conv_type == 0)
				continue ;
			if (el->pos == curr_pos || el->precision_ref == curr_pos
				|| el->width_ref == curr_pos)
			{
				was_pos = 1;
				arg = arg_new();
				if (el->width_ref == curr_pos || el->precision_ref == curr_pos)
					arg->val_i = va_arg(*ap, int);
				else
					push_arg(el, arg, ap);
				
				ft_llist_add(args, arg);
			}
		}
		if (!was_pos)
			break ;
		++curr_pos;
	}
	return (args);
}

t_print_arg	*get_arg(t_llist *args, int pos)
{
	if ((int)args->count - 1 < pos || pos < 0)
		return (arg_new());
	return ((t_print_arg*)ft_llist_get(args, pos));
}
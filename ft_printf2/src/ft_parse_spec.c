/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:07:27 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 15:07:29 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int				ft_parse_len_or_flags(t_printf_elem *el, char **pptr)
{
	char	support;
	char	*ptr;
	int		ok;

	ok = 1;
	ptr = *pptr;
	if ((support = ft_parse_len_mod(&ptr)) != 0)
	{
		if (ft_len_cost(el->length_mod) < ft_len_cost(support))
			el->length_mod = support;
	}
	else if ((support = ft_parse_flag(&ptr)) != 0)
		el->flags |= support;
	else
		ok = 0;
	*pptr = ptr;
	return (ok);
}

int				ft_parse_precision(t_printf_elem *el, char **pptr, int *pos)
{
	int		number;
	char	*ptr;
	int		ok;

	ok = 0;
	ptr = *pptr;
	if (*ptr == '.')
	{
		++ptr;
		if (*ptr == '*')
		{
			number = ft_parse_get_pos(&ptr);
			el->precision_pos = ft_parse_num_or_pos(number, pos);
		}
		else
		{
			el->precision = ft_parse_get_number(&ptr);
			el->precision_seted = 1;
		}
		ok = 1;
	}
	*pptr = ptr;
	return (ok);
}

void			ft_parse_spec_inner(t_printf_elem *el, char **fmt, int *pos)
{
	char	*ptr;
	int		number;

	ptr = *fmt;
	while (*ptr)
	{
		if (ft_parse_len_or_flags(el, &ptr))
			;
		else if (*ptr == '*')
		{
			number = ft_parse_get_pos(&ptr);
			el->width_pos = ft_parse_num_or_pos(number, pos);
			el->width_seted = 0;
		}
		else if ('1' <= *ptr && *ptr <= '9')
		{
			el->width = ft_parse_get_number(&ptr);
			el->width_seted = 1;
		}
		else if (!ft_parse_precision(el, &ptr, pos))
			break ;
		++ptr;
	}
	*fmt = ptr;
}

char			ft_check_reference(t_printf_elem *el, char **pptr, int *pos)
{
	char	*ptr;
	char	use_pos;

	use_pos = 0;
	ptr = *pptr;
	if (ft_parse_is_reference(ptr))
	{
		el->pos = ft_parse_get_number(&ptr);
		*pos = el->pos + 1;
		++ptr;
	}
	else
		use_pos = 1;
	*pptr = ptr;
	return (use_pos);
}

t_printf_elem	*ft_parse_spec(char **fmt, int *pos, char *add)
{
	char			*ptr;
	t_printf_elem	*el;
	char			use_pos;

	ptr = *fmt;
	++ptr;
	el = ft_printf_elem_new();
	use_pos = ft_check_reference(el, &ptr, pos);
	ft_parse_spec_inner(el, &ptr, pos);
	if (*ptr)
	{
		if (use_pos && ft_parse_is_conv_spec(*ptr))
			el->pos = (*pos)++;
		el->conv_type = *ptr;
		*fmt = ptr + 1;
		*add = 1;
	}
	else
	{
		*fmt = ptr;
		*add = 0;
		return (NULL);
	}
	return (el);
}

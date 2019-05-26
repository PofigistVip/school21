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

int			ft_parse_num_or_pos(int number, int *pos)
{
	if (number >= 0)
		return (number);
	return ((*pos)++);
}

void			ft_parse_str_elem(t_printf_elem *el, char **fmt, char *ptr)
{
	int		len;
	char	*raw;

	el->conv_type = 0;
	len = ptr - *fmt;
	raw = (char*)malloc(len + 1);
	ft_memcpy(raw, *fmt, len);
	*(raw + len) = '\0';
	el->raw_str = raw;
	*fmt = ptr;
}

int				ft_parse_get_pos(char **fmt)
{
	char	*ptr;
	int		number;

	ptr = *fmt;
	if (ft_parse_is_reference(ptr + 1))
	{
		++ptr;
		number = ft_parse_get_number(&ptr);
		*fmt = ptr;
		return (number);
	}
	return (-1);
}

int				ft_len_cost(char len)
{
	if (len == 0)
		return (0);
	if (len == 'j')
		return (sizeof(intmax_t));
	if (len == 'z')
		return (sizeof(size_t));
	if (len == 't')
		return (sizeof(void*));
	if (len == 'H')
		return (sizeof(char));
	if (len == 'h')
		return (sizeof(short int));
	if (len == 'M' || len == 'q')
		return (sizeof(long long int));
	if (len == 'L')
		return (sizeof(long double));
	if (len == 'l')
		return (sizeof(long int));
	return (0);
}

int				ft_parse_spec_inner_end(t_printf_elem *el, char **pptr, int *pos)
{
	char	*ptr;
	char	ok;
	int		number;

	ptr = *pptr;
	ok = 0;
	if ('1' <= *ptr && *ptr <= '9')
	{
		el->width = ft_parse_get_number(&ptr);
		el->width_seted = 1;
		ok = 1;
	}
	else if (*ptr == '.')
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
	char	support;
	int		number;

	ptr = *fmt;
	while (*ptr)
	{
		if ((support = ft_parse_len_mod(&ptr)) != 0)
		{
			if (ft_len_cost(el->length_mod) < ft_len_cost(support))
				el->length_mod = support;
		}
		else if ((support = ft_parse_flag(&ptr)) != 0)
		{
			el->flags |= support;
		}
		else if (*ptr == '*')
		{
			number = ft_parse_get_pos(&ptr);
			el->width_pos = ft_parse_num_or_pos(number, pos);
			el->width_seted = 0;
		}
		else if (!ft_parse_spec_inner_end(el, &ptr, pos))
			break ;
		++ptr;
	}
	*fmt = ptr;
}

t_printf_elem	*ft_parse_spec(char **fmt, int *pos, char *add)
{
	char			*ptr;
	t_printf_elem	*el;
	char			use_pos;

	ptr = *fmt;
	++ptr;
	el = ft_printf_elem_new();
	use_pos = 0;
	if (ft_parse_is_reference(ptr))
	{
		el->pos = ft_parse_get_number(&ptr);
		*pos = el->pos + 1;
		++ptr;
	}
	else
		use_pos = 1;
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

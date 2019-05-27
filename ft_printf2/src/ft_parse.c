/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:28:43 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:28:48 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_printf_elem	*ft_printf_elem_new(void)
{
	t_printf_elem	*el;

	if ((el = (t_printf_elem*)malloc(sizeof(t_printf_elem))) == NULL)
		return (NULL);
	ft_bzero(el, sizeof(t_printf_elem));
	return (el);
}

void			ft_printf_elem_add(t_printf_elem **els, t_printf_elem *el)
{
	t_printf_elem	*curr;

	if (*els)
	{
		curr = *els;
		while (curr->next)
			curr = curr->next;
		curr->next = el;
	}
	else
	{
		*els = el;
	}
}

t_printf_elem	*ft_parse_rawstr(char **fmt)
{
	char			*ptr;
	t_printf_elem	*el;
	size_t			len;
	char			*raw;

	ptr = *fmt;
	while (*ptr && *ptr != '%')
		++ptr;
	if ((el = ft_printf_elem_new()) == NULL)
		return (NULL);
	el->conv_type = 0;
	len = ptr - *fmt;
	if ((raw = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(raw, *fmt, len);
	*(raw + len) = '\0';
	el->raw_str = raw;
	*fmt = ptr;
	return (el);
}

t_printf_elem	*ft_parse(char *fmt, int *pos)
{
	t_printf_elem	*els;
	t_printf_elem	*curr;
	char			add;
	int				ok;

	ok = 1;
	els = 0;
	*pos = 1;
	while (*fmt)
	{
		add = 0;
		if (*fmt == '%')
		{
			curr = ft_parse_spec(&fmt, pos, &add);
		}
		else
		{
			if ((curr = ft_parse_rawstr(&fmt)) == NULL)
			{
				ok = 0;
				break ;
			}
			add = 1;
		}
		if (add)
			ft_printf_elem_add(&els, curr);
	}
	if (!ok)
	{
		ft_memfree(els, 0);
		exit(-1);
	}
	return (els);
}

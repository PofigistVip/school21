/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spec_utility.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:12:21 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:12:24 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_parse_num_or_pos(int number, int *pos)
{
	if (number >= 0)
		return (number);
	return ((*pos)++);
}

void	ft_parse_str_elem(t_printf_elem *el, char **fmt, char *ptr)
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

int		ft_parse_get_pos(char **fmt)
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

int		ft_len_cost(char len)
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

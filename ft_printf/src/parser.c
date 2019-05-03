/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:17:16 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 12:17:19 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int 			is_conversion_specifier(char c)
{
	return (c == 'd' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'x' || c == 'X' || c == 'e' || c == 'E'
		|| c == 'f' || c == 'F' || c == 'g' || c == 'G'
		|| c == 'a' || c == 'A' || c == 'c' || c == 's'
		|| c == 'C' || c == 'S' || c == '%');
}

unsigned char	is_flag(char c)
{
	if (c == '#')
		return (1);
	if (c == '0')
		return (2);
	if (c == '-')
		return (4);
	if (c == ' ')
		return (8);
	if (c == '+')
		return (16);
	if (c == '\'')
		return (32);
	if (c == 'I')
		return (64);
	return (0);
}

void	get_num_or_ref(const char **format, int *num, int *ref)
{
	while(ft_isdigit(**format))
		++(*format);
	if (**format == '$')
		*ref = 1;
	else
	{
		*num = 5;
		--(*format);
	}
}

t_print_elem	*new_print_elem(void)
{
	t_print_elem	*elem;

	elem = (t_print_elem*)malloc(sizeof(t_print_elem));
	elem->conv_type = 0;
	elem->str_len = 0;
	elem->flags = 0;
	elem->width = 0;
	elem->width_ref = 0;
	elem->precision = 0;
	elem->precision_ref = 0;
	elem->pos = 0;
	return (elem);
}

void			destroy_print_elem(t_print_elem *elem)
{
	free(elem->str);
}

t_llist		*parse_format(const char *format)
{
	t_llist			*llist;
	t_print_elem	*el;
	size_t			n;
	char			wait_width;	
	int				current_pos;	

	llist = ft_llist_create(sizeof(t_print_elem));
	n = 0;
	current_pos = 1;
	while (*format)
	{
		if (*format == '%')
		{
			if (n != 0)
			{
				el = new_print_elem();
				el->str_len = n;
				el->str = (char*)malloc(n);
				el->conv_type = '\0';
				ft_memcpy(el->str, format - n, n);
				ft_llist_add(llist, el);
				n = 0;
			}
			el = new_print_elem();
			wait_width = 1;
			++format;
			if (ft_isdigit(*format))
				get_ref(&format, &el->pos);
			else
				el->pos = current_pos++;
			while (*(++format) && !is_conversion_specifier(*format))
			{
				if (ft_isdigit(*format))
				{
					if (wait_width)
						get_num_or_ref(&format, &el->width, &el->width_ref);
					//else
					//	get_num_or_ref(&format, &el->precision, &el->precision_ref);
				}	
				if (*format == '.')
					wait_width = 0;
				else
					el->flags |= is_flag(*format);
			}
			if (!*format)
				return (NULL);//незакончен форматный вывод
			el->conv_type = *format;
			ft_llist_add(llist, el);
		}
		else
			++n;
		++format;
		
	}
	if (n != 0)
	{
		el = new_print_elem();
		el->str_len = n;
		el->str = (char*)malloc(n);
		ft_memcpy(el->str, format - n, n);
		ft_llist_add(llist, el);
	}
	return (llist);
}
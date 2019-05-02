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

int is_conversion_specifier(char c)
{
	return (c == 'd' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'x' || c == 'X' || c == 'e' || c == 'E'
		|| c == 'f' || c == 'F' || c == 'g' || c == 'G'
		|| c == 'a' || c == 'A' || c == 'c' || c == 's'
		|| c == 'C' || c == 'S' || c == '%');
}

t_print_elem	*new_print_elem(void)
{
	t_print_elem	*elem;

	elem = (t_print_elem*)malloc(sizeof(t_print_elem));
	elem->conv_type = '\0';
	elem->str_len = 0;
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

	llist = ft_llist_create(sizeof(t_print_elem));
	n = 0;
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
				//llist не должен копировать объект, а просто хранит его ссылку
				n = 0;
			}
			el = new_print_elem();
			while (*(++format) && !is_conversion_specifier(*format))
			{
				
			}
			if (!*format)
				return (NULL);//незакончен форматный вывод
			el->conv_type = *format;
			//ft_llist_add(llist, el);
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
		//llist не должен копировать объект, а просто хранит его ссылку
	}
	return (llist);
}
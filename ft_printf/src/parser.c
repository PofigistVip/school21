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

int				is_reference(const char *str)
{
	while (*str && ft_isdigit(*str))
		++str;
	return (*str == '$');
}

char	is_length_mod(const char *str)
{
	if (*str == 'h' && *(str + 1) == 'h')
		return ('H');
	if (*str == 'l' && *(str + 1) == 'l')
		return ('M');
	if (*str == 'h')
		return ('h');
	if (*str == 'l')
		return ('l');
	if (*str == 'L')
		return ('L');
	if (*str == 'q')
		return ('q');
	if (*str == 'j')
		return ('j');
	if (*str == 'z')
		return ('z');
	if (*str == 't')
		return ('t');
	return (0);
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

int				get_num(const char **format)
{
	int		num;

	num = 0;
	while(ft_isdigit(**format))
	{
		num = num * 10 + ((**format) - '0');
		++(*format);
	}
	--(*format);
	return (num);
}

t_print_elem	*new_print_elem(void)
{
	t_print_elem	*elem;

	elem = (t_print_elem*)malloc(sizeof(t_print_elem));
	elem->str = ft_lstr_new_empty();
	elem->conv_type = 0;
	elem->flags = 0;
	elem->width = -1;
	elem->width_ref = 0;
	elem->precision = -1;
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
	int				current_pos;
	char			flag;
	char			len_mod;

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
				ft_lstr_insert_sn(el->str, (char*)format - n, n, 0);
				ft_llist_add(llist, el);
				n = 0;
			}
			el = new_print_elem();
			++format;
			if (is_reference(format))
			{
				el->pos = get_num(&format);
				current_pos = el->pos + 1;
				format += 2;
			}
			else
				el->pos = current_pos++;
			while (*format && !is_conversion_specifier(*format))
			{
				len_mod = is_length_mod(format);
				flag = is_flag(*format);
				if (len_mod)
				{
					el->length_mod = len_mod;
					if (len_mod == 'H' || len_mod == 'M')
						++format;
				}
				else if (flag)
					el->flags |= flag;
				else if (*format == '*')
				{
					++format;
					if (is_reference(format))
						el->width_ref = get_num(&format);
					else
						el->width_ref = current_pos++;
					
				}
				else if (ft_isdigit(*format))
					el->width = get_num(&format);
				else if (*format == '.')
				{
					++format;
					if (*format == '*')
					{
						++format;
						if (is_reference(format))
							el->precision_ref = get_num(&format);
						else
							el->precision_ref = current_pos++;
					}
					el->precision = get_num(&format);
				}
				++format;
			}
			if (!*format)
				return (llist);//незакончен форматный вывод, free mem
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
		ft_lstr_insert_sn(el->str, (char*)format - n, n, 0);
		ft_llist_add(llist, el);
	}
	return (llist);
}
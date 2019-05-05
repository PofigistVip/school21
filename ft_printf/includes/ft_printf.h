/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:00:43 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/28 13:00:47 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <stdarg.h>
# include "libft.h"

/*
** conv_type: type specifier
** length_mod: length specifier
**		hh = H
**		ll = M
** flags:
** '#' - 1,
** '0' - 2,
** '-' - 4,
** ' ' - 8,
** '+' - 16
** "'" - 32,
** 'I' - 64
** 
** pos - позиция аргумента
*/

typedef struct	s_print_elem
{
	char			conv_type;
	char			length_mod;

	unsigned char	flags;

	int				width;
	int				width_ref;
	int				precision;
	int				precision_ref;
	int				pos;
	t_lstr			*str;
	
}				t_print_elem;

typedef struct	s_print_arg
{
	int						pos;

	void					*ptr;
	long long int			val_i;
	unsigned long long int	val_ui;
	double					val_d;
}				t_print_arg;


t_llist			*parse_format(const char *format);

t_llist	*push_args(t_llist *llist, va_list *ap);
t_print_arg	*get_arg(t_llist *args, int pos);

int				ft_printf(const char *format, ...);

#endif
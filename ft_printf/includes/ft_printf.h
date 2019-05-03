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
# include "libft.h"

/*
** flags:
** '#' - 1,
** '0' - 2,
** '-' - 4,
** ' ' - 8,
** '+' - 16
** "'" - 32,
** 'I' - 64
*/

typedef struct	s_print_elem
{
	char	conv_type;

	unsigned char	flags;


	int				width;
	int				precision;
	char	*str;
	size_t	str_len;

}				t_print_elem;

t_llist			*parse_format(const char *format);

int				ft_printf(const char *format, ...);

#endif
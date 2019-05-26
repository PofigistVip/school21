/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_cC.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:30:04 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:30:08 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_c(int fd, t_printf_elem *el)
{
	int		i;
	int		width;
	char	space;
	char	symb;

	symb = (unsigned char)el->arg->val_i;
	width = el->width;
	if (width <= 1)
	{
		write(fd, &symb, 1);
		return (1);
	}
	i = 1;
	space = (el->flags & FT_PRINTF_ZERO) ? '0' : ' ';
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, &symb, 1);
		while (i++ < width)
			write(fd, &space, 1);
		return (width);
	}
	while (i++ < width)
		write(fd, &space, 1);
	write(fd, &symb, 1);
	return (width);
}

int		ft_display_big_c(int fd, t_printf_elem *el)
{
	t_lstr	*lstr;
	int		len;

	lstr = ft_lstr_new_empty();
	ft_putwchar(lstr, el->arg->val_wc);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, 0);
	else
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, lstr->length);
	ft_lstr_put_fd(lstr, fd);
	len = lstr->length;
	ft_lstr_destroy(&lstr);
	return (len);
}

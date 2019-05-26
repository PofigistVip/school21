/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_raw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:43:43 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 12:43:48 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_display_raw(int fd, t_printf_elem *el)
{
	ft_putstr_fd(el->raw_str, fd);
	return ((int)ft_strlen(el->raw_str));
}

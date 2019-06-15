/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:10:03 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/15 10:10:05 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isint(const char *str)
{
	int		num;
	int		sign;

	num = 0;
	while (*str && ('\t' <= *str && *str <= '\r'))
		++str;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while ('0' <= *str && *str <= '9')
	{
		
	}
	if (*str != '\0')
		return (0);
	return (1);
}
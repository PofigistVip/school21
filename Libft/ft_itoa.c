/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:56:03 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/13 14:04:31 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_itoa(int n)
{
	char	sign;
	char	size;
	int		num;
	char	*str;

	num = n;
	size = (num < 0) ? 2 : 1;
	while (num >= 10 || num <= -10)
	{
		size++;
		num /= 10;
	}
	str = (char*)malloc(size + 1);
	str[size] = '\0';
	sign = (n < 0) ? -1 : 1;
	if (n < 0)
		*str = '-';
	while (n >= 10 || n <= -10)
	{
		str[size - 1] = (n % 10) * sign + '0';
		--size;
		n /= 10;
	}
	str[size - 1] = (n % 10) * sign + '0';
	return (str);
}

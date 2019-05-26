/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:34:45 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 14:34:46 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_uitoa_base(unsigned long long int nbr, int base, char upper)
{
	unsigned long long int	n;
	int						len;
	char					*str;
	char					*base_str;

	base_str = (upper) ? "0123456789ABCDEF" : "0123456789abcdef";
	len = 1;
	n = nbr;
	while ((n /= base) != 0)
		++len;
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len > -1)
	{
		str[len--] = base_str[nbr % base];
		nbr /= base;
	}
	return (str);
}

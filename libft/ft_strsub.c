/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:16:55 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 10:55:10 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*s_ptr;
	char	*sub_ptr;

	if (s == NULL)
		return (NULL);
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	s_ptr = (char*)s + start;
	sub_ptr = str;
	while (len--)
	{
		*sub_ptr = *s_ptr;
		++sub_ptr;
		++s_ptr;
	}
	*sub_ptr = '\0';
	return (str);
}

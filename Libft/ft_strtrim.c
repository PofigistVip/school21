/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:41:35 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 11:29:41 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

static size_t	ft_space_start_count(char const *s)
{
	size_t	at_start;

	at_start = 0;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
	{
		++at_start;
		++s;
	}
	return (at_start);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;
	size_t	at_start;
	size_t	at_end;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	at_end = 0;
	at_start = ft_space_start_count(s);
	i = len - 1;
	if (at_start != len)
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		{
			--i;
			++at_end;
		}
	if ((str = (char*)malloc(len - at_start - at_end + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, s + at_start, len - at_start - at_end);
	str[len - at_start - at_end] = '\0';
	return (str);
}

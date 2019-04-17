/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:37:37 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 10:47:51 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*arr;

	len = ft_strlen(s1);
	if ((arr = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		arr[i] = s1[i];
		++i;
	}
	return (arr);
}

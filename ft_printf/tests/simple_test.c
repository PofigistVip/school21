/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:10:24 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/28 13:17:21 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	char	*format = "Hello, %2$hhd. Nice to %1$d meet you %d!\n";
	char	*str1 = "Larlyne";
	int		int1 = 5;
	int		int2 = 69;
	int		int3 = 100;

	printf("=-=-=-=-=\n");
	printf(format, int1, int2, int3);
	printf("=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, int1, int2, int3);
		printf("=-=-=-=-=\n");
	}
	return (0);
}

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
	//bugs:
	//проверить флаги после чисел на MacOS!
	char	*format = "@moulitest: %#.o %#.0o";
	char	*str1 = NULL;
	char	char1 = 65;
	int		int1 = 0;
	int		int2 = 3;

	printf("=-=-=-=-=\n");
	printf(format, int1, int1);
	printf("\n=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, int1, int1);
		printf("\n=-=-=-=-=\n");
	}
	return (0);
}

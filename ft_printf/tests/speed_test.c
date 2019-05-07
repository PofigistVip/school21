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

#include <limits.h>
#include <stdio.h>
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	//bugs:
	//проверить флаги после чисел на MacOS!
	char	*format = "%s";
	char	*str1 = "Larlyne";
	char	char1 = 65;
	int		int1 = 42;
	int		int2 = 3;

	printf("=-=-=-=-=\n");
	if (argc == 1)
		printf(format, &int1, int1);
	else
		ft_printf(format, &int1, int1);
	printf("\n=-=-=-=-=\n");
	return (0);
}
